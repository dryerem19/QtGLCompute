#include "glcomputespace.h"

GLComputeSpace::GLComputeSpace()
    : QOffscreenSurface(), _context(nullptr)
{

}

void GLComputeSpace::init()
{
    QSurfaceFormat format;
    format.setMajorVersion(4);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);

    setFormat(format);
    create();

    _context = new QOpenGLContext(this);
    _context->setFormat(format);
    _context->create();

    _context->makeCurrent(this);
    initializeOpenGLFunctions();
}

void GLComputeSpace::start()
{
    if (!_program.addShaderFromSourceFile(QOpenGLShader::Compute, ":/test.comp")) {
        qFatal("Cannot load compute shader file");
    }

    if (!_program.link()) {
        qFatal("Cannot link compute shader");
    }

    const quint32 N = 4096 * 4096;

    // Create input buffer
    if (!_inputBuffer.create()) {
        qFatal("Cannot create input buffer");
    }
    _inputBuffer.setUsagePattern(QOpenGLBuffer::DynamicCopy);
    _inputBuffer.bind();
    _inputBuffer.allocate(nullptr, N * sizeof(quint32));

    // Create output buffer
    if (!_outputBuffer.create()) {
        qFatal("Cannot create output buffer");
    }
    _outputBuffer.setUsagePattern(QOpenGLBuffer::DynamicCopy);
    _outputBuffer.bind();
    _outputBuffer.allocate(nullptr, N * sizeof(quint32));


    // Write to input shader buffer
    _inputBuffer.bind();
    quint32* dataIn = (quint32*)_inputBuffer.map(QOpenGLBuffer::WriteOnly);
    for (quint32 i = 0; i < N; ++i) {
        *dataIn = i + 2;
        dataIn++;
    }
    _inputBuffer.unmap();

    // Bind input and output buffer to shader
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _inputBuffer.bufferId());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, _outputBuffer.bufferId());

    {
        QElapsedTimer timer;
        timer.start();

        testCPU();

        qDebug() << "CPU" << timer.elapsed() << "milliseconds";
        qDebug() << "CPU" << timer.nsecsElapsed() << "nanoseconds";
    }

    QElapsedTimer timer;
    timer.start();

    // Compute
    if (_program.bind())
    {
        glDispatchCompute(N, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    }

    qDebug() << "GPU" << timer.elapsed() << "milliseconds";
    qDebug() << "GPU" << timer.nsecsElapsed() << "nanoseconds";

    // Read result
//    _outputBuffer.bind();
//    quint32* dataOut = (quint32*)_outputBuffer.map(QOpenGLBuffer::ReadOnly);
//    if (dataOut)
//    {
//        for (quint32 i = 0; i < N; ++i) {
//            qDebug() << *dataOut;
//            dataOut++;
//        }
//        _outputBuffer.unmap();
//    }
    //    _outputBuffer.release();
}

void GLComputeSpace::testCPU()
{
    const quint32 N = 4096 * 4096;

    quint32* buffer = new quint32[N];
    for (quint32 i = 0; i < N; ++i)
    {
        buffer[i] = (i + 2) * 2;
    }

    delete[] buffer;
}
