#ifndef CODERUNNER_H
#define CODERUNNER_H

#include <QObject>
#include <QWidget>
#include <windows.h>
#include "terminal.h"



class QString;




class CodeRunner:public Terminal
{
    Q_OBJECT
public:
    CodeRunner(QWidget* parent);
    ~CodeRunner();

    enum class Mode{
        UnKown,
        Cpp,
        Python
    };

    void setMode(QString &fileType);

    void runCode();

    void runCppCode();

    void runPythonCode();

    void searchRunner();

    void setRunFile(QString &file);

    QString searchFiles(const QString &dirPath, const QString &searchPattern);

    BOOL WinStartProcess(TCHAR* lpApplicationName, TCHAR* lpCommandLine);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    QString FileType;
    QString runFile;
    QStringList runFileList;

    Mode RunMode=Mode::UnKown;

    QString PythonRunner;
    QString CppRunner;

    bool isRunnerExist;
};

#endif // CODERUNNER_H
