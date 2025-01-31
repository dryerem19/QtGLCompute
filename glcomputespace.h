#ifndef GLCOMPUTESPACE_H
#define GLCOMPUTESPACE_H

#include <QDebug>
#include <QOpenGLBuffer>
#include <QElapsedTimer>
#include <QOffscreenSurface>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_3_Core>

class GLComputeSpace final : public QOffscreenSurface, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    explicit GLComputeSpace();
    void init();
    void start();
    void testCPU();
private:
    QOpenGLShaderProgram _program;
    QOpenGLBuffer _outputBuffer;
    QOpenGLBuffer _inputBuffer;
    QOpenGLContext* _context;
};

#endif // GLCOMPUTESPACE_H
