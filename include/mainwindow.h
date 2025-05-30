#pragma once

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include "zoomablegraphicsview.h"
#include <QGraphicsScene>
#include <QtSvgWidgets/QGraphicsSvgItem>

namespace travel {
    class Projet;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCalculateClicked();

private:
    QComboBox *startComboBox;
    QComboBox *endComboBox;
    QPushButton *calculateButton;
    QTextEdit *resultText;

    void loadStations();
    ZoomableGraphicsView *mapView;
    QGraphicsScene *mapScene;
};
