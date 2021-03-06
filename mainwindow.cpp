#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include "editorscene.h"
#include "basicshapeitem.h"
#include "graphics_view_zoom.h"
#include "svgreader.h"
#include <QDebug>
#include <QStyleFactory>
#include <QApplication>
#include <QGraphicsProxyWidget>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->WorkPlaceGV->setDragMode(QGraphicsView::RubberBandDrag);

    LoadTools();

    Graphics_view_zoom *z = new Graphics_view_zoom(ui->WorkPlaceGV);
    z->set_modifiers(Qt::NoModifier);

    setAcceptDrops(true);

    scene = new EditorScene();

    scene->addPixmap(QString(":/Resources/frames/startscreen.png"));
    ui->WorkPlaceGV->setScene(scene);

    new QShortcut(QKeySequence::Delete, this, SLOT(delete_selected()));

}

void MainWindow::LoadTools()
{
    //WigetLoad
    ui->ToolBoxLW->setDragEnabled(true);
    ui->ToolBoxLW->setAcceptDrops(true);
    ui->ToolBoxLW->setDropIndicatorShown(true);
    ui->ToolBoxLW->setDefaultDropAction(Qt::MoveAction);

    ui->ToolBoxLW->setIconSize(QSize(100,100));

    item = new QListWidgetItem(QIcon(":/Resources/items/button.png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem(QIcon(":/Resources/items/label.png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem(QIcon(":/Resources/items/checkbox.png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem(QIcon(":/Resources/items/radiobutton .png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem(QIcon(":/Resources/items/slider.png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem(QIcon(":/Resources/items/textarea.png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem(QIcon(":/Resources/items/textinput.png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem(QIcon(":/Resources/items/toggle.png"),nullptr);
    ui->ToolBoxLW->addItem(item);

    item = new QListWidgetItem("Add marker");
    ui->ToolBoxLW->addItem(item);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ToolBoxLW_itemDoubleClicked(QListWidgetItem *item)
{

    if (ui->ToolBoxLW->item(0) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/button.png");
    }

    if (ui->ToolBoxLW->item(1) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/label.png");
    }

    if (ui->ToolBoxLW->item(2) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/checkbox.png");
    }

    if (ui->ToolBoxLW->item(3) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/radiobutton .png");
    }

    if (ui->ToolBoxLW->item(4) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/slider.png");
    }

    if (ui->ToolBoxLW->item(5) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/textarea.png");
    }

    if (ui->ToolBoxLW->item(6) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/textinput.png");

    }

    if (ui->ToolBoxLW->item(7) == item)
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,30,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(":/Resources/items/toggle.png");
    }

    if (ui->ToolBoxLW->item(8) == item)
    {
        /// до реализовать жесткие размеры

        auto *mark_color = new QGraphicsRectItem(0, 0, 100, 40);
        auto *mark_text =new QGraphicsTextItem(mark_color);

        mark_text->setTextWidth(100);
        mark_text->setPlainText("Add text");

        scene->addItem(mark_color);
        mark_text->setTextInteractionFlags(Qt::TextEditorInteraction);
        mark_color->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);

        mark_color->setBrush(Qt::green);
    }
}


void MainWindow::SaveProject()
{
    QMessageBox SaveQstnMsgBox;
    SaveQstnMsgBox.setWindowTitle("Save project");
    SaveQstnMsgBox.setText("Finish your project?");
    QPushButton *YESButton = SaveQstnMsgBox.addButton(QMessageBox::Yes);
    QPushButton *NOButton = SaveQstnMsgBox.addButton(QMessageBox::No);

    SaveQstnMsgBox.exec();

    if (SaveQstnMsgBox.clickedButton()==YESButton)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                        tr("PNG Files (*.png);;JPG Files (*.jpg)"));
        if (fileName != "")
        {
            QFile file(fileName);
            QImage image(ui->WorkPlaceGV->width(),ui->WorkPlaceGV->height(), QImage::Format_ARGB32_Premultiplied);
            QPainter painter(&image);
            ui->WorkPlaceGV->render(&painter);
            image.save(fileName);
        }
        else
        {
            if (SaveQstnMsgBox.clickedButton()==NOButton)
            {
                SaveQstnMsgBox.close();
            }
        }
    }
}

void MainWindow::OpenProject()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open Image File",QDir::currentPath());
    BasicShapesItem *item = new BasicShapesItem(12,12,100,100,BasicShapesItem::ITEM_TOOL,scene);
    item->setPixmap(fileName);
    ui->WorkPlaceGV->setScene(scene);
}

void MainWindow::delete_selected()
{
    foreach(QGraphicsItem *item, scene->selectedItems())
    {
        delete item;
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event) {/// проект перекидывается криво!

    foreach(QUrl url, event->mimeData()->urls())
    {
        BasicShapesItem *item = new BasicShapesItem(12,12,100,100,BasicShapesItem::ITEM_TOOL,scene);
        item->setPixmap(url.toLocalFile());
        item->setPos(ui->WorkPlaceGV->mapToScene(ui->WorkPlaceGV->viewport()->mapFrom(this, event->pos())));
    }

}

void MainWindow::on_actionOpen_triggered()
{
    OpenProject();
}

void MainWindow::on_actionSave_As_triggered()
{
    if ( scene->items().empty())
    {
        QMessageBox TrueInputMsgBox;
        TrueInputMsgBox.setWindowTitle("Data entry error");
        TrueInputMsgBox.setText("Please check that your project is not empty.");
        QPushButton *OKButton = TrueInputMsgBox.addButton(QMessageBox::Ok);
        TrueInputMsgBox.exec();

    }
    else
    {
        SaveProject();
    }
}

void MainWindow::on_actionAddDescktop_Frame_triggered()
{
    scene = new EditorScene();
    scene->clear();
    ui->WorkPlaceGV->setBackgroundBrush(QPixmap(":/Resources/frames/bg_grid.gif"));
    scene->addPixmap(QString(":/Resources/frames/tablet_frame.png"));
    ui->WorkPlaceGV->setScene(scene);
    ui->WorkPlaceGV->show();
    setAcceptDrops(true);
}

void MainWindow::on_actionAdd_Mobile_Frame_triggered()
{
    scene = new EditorScene();
    scene->clear();
    ui->WorkPlaceGV->setBackgroundBrush(QPixmap(":/Resources/frames/bg_grid.gif"));
    scene->addPixmap(QString(":/Resources/frames/phone_frame.png"));
    ui->WorkPlaceGV->setScene(scene);
    ui->WorkPlaceGV->show();
    setAcceptDrops(true);
}

void MainWindow::on_actionAdd_Empty_Frame_triggered()
{
    scene = new EditorScene();
    scene->clear();
    scene->addPixmap((QPixmap(":/Resources/frames/bg_grid.gif")));
    ui->WorkPlaceGV->setScene(scene);
    ui->WorkPlaceGV->show();
    setAcceptDrops(true);
}

void MainWindow::SaveSVG()
{
    QString newPath = QFileDialog::getSaveFileName(this, trUtf8("Save SVG"),
                                                   path, tr("SVG files (*.svg)"));

    if (newPath.isEmpty())
        return;

    path = newPath;

    QSvgGenerator generator;
    generator.setFileName(path);
    generator.setSize(QSize(scene->width(), scene->height()));
    generator.setViewBox(QRect(0, 0, scene->width(), scene->height()));
    generator.setTitle(trUtf8("SVG Example"));
    generator.setDescription(trUtf8("File created by SVG Example"));


    QPainter painter;
    painter.begin(&generator);
    scene->render(&painter);
    painter.end();

}


void MainWindow::OpenSVG()
{
    //    QString newPath = QFileDialog::getOpenFileName(this, trUtf8("Open SVG"),
    //                                                   path, tr("SVG files (*.svg)"));
    //    if (newPath.isEmpty())
    //        return;

    //    path = newPath;
    //    scene->clear();

    //    scene->setSceneRect(SvgReader::getSizes(path));
}

void MainWindow::on_actionSave_SVG_triggered()
{
    SaveSVG();
}

void MainWindow::on_actionOpen_SVG_triggered()
{
    OpenSVG();
}
