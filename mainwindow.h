#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QListWidget>
#include <QMainWindow>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPushButton>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void LoadTools();
    void SaveProject();
    void OpenProject();


protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);

private slots:
    void on_ToolBoxLW_itemDoubleClicked(QListWidgetItem *item);

    void on_actionAdd_Descktop_Frame_triggered();

    void on_actionAdd_Mobile_Frame_triggered();

    void on_actionAdd_Empty_Frame_triggered();

    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

    void delete_selected();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QListWidgetItem *item;

};
#endif // MAINWINDOW_H
