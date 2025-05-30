#include "mainwindow.h"
#include "Projet.hpp"
#include "zoomablegraphicsview.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>
#include <QGraphicsSvgItem>
#include <stdexcept>

extern travel::Projet projet;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    startComboBox = new QComboBox();
    endComboBox = new QComboBox();
    calculateButton = new QPushButton("Calculer le trajet");
    resultText = new QTextEdit();
    resultText->setReadOnly(true);

    layout->addWidget(new QLabel("Station de départ :"));
    layout->addWidget(startComboBox);
    layout->addWidget(new QLabel("Station d'arrivée :"));
    layout->addWidget(endComboBox);
    layout->addWidget(calculateButton);
    layout->addWidget(new QLabel("Trajet :"));
    layout->addWidget(resultText);

    // Carte SVG
    mapScene = new QGraphicsScene(this);
    mapView = new ZoomableGraphicsView(this);
    mapView->setScene(mapScene);
    mapView->setMinimumHeight(500);

    layout->addWidget(new QLabel("🗺️ Carte du métro (SVG) :"));
    layout->addWidget(mapView);

    QGraphicsSvgItem *svgItem = new QGraphicsSvgItem("data/plan.svg");
    mapScene->addItem(svgItem);
    svgItem->setZValue(-1);

    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateClicked);

    setCentralWidget(central);
    setWindowTitle("Calculateur de trajet RATP");

    loadStations();
}

MainWindow::~MainWindow() {}

void MainWindow::loadStations() {
    auto names = projet.getAllStationNames();
    QStringList qnames;
    for (const std::string& name : names)
        qnames << QString::fromStdString(name);

    startComboBox->addItems(qnames);
    endComboBox->addItems(qnames);
}

void MainWindow::onCalculateClicked() {
    std::string start = startComboBox->currentText().toStdString();
    std::string end = endComboBox->currentText().toStdString();

    try {
        auto path = projet.compute_travel(start, end);
        const auto& stations = projet.get_stations_hashmap();

        if (path.empty()) {
            resultText->setText("❌ Aucun trajet trouvé.");
            return;
        }

        uint64_t startId = path.front().first;
        uint64_t endId = path.back().first;

        const auto& startStation = stations.at(startId);
        const auto& endStation = stations.at(endId);

        QString html;

        html += "<h3>🚇 Trajet de <b>" + QString::fromStdString(start) +
                "</b> à <b>" + QString::fromStdString(end) + "</b></h3>";

        html += "<p><b>📍 Départ :</b> " + QString::fromStdString(startStation.name).toHtmlEscaped() +
                " — <i>" + QString::fromStdString(startStation.address).toHtmlEscaped() + "</i></p>";

        html += "<p><b>🏁 Arrivée :</b> " + QString::fromStdString(endStation.name).toHtmlEscaped() +
                " — <i>" + QString::fromStdString(endStation.address).toHtmlEscaped() + "</i></p>";

        html += "<hr>";

        std::string previousLine = "";
        int totalTime = 0;

        for (size_t i = 0; i < path.size(); ++i) {
            uint64_t id = path[i].first;
            int time = static_cast<int>(path[i].second);
            const auto& station = stations.at(id);

            std::string currentLine = station.line_name;

            // Affichage changement de ligne
            if (!previousLine.empty() && currentLine != previousLine) {
                html += "<p><b>🔁 Changement : Ligne " + QString::fromStdString(previousLine).toHtmlEscaped() +
                        " → Ligne " + QString::fromStdString(currentLine).toHtmlEscaped() + "</b></p>";
            }

            html += "• " + QString::fromStdString(station.name).toHtmlEscaped()
                  + " <i>(Ligne " + QString::fromStdString(currentLine).toHtmlEscaped()
                  + ")</i> — <span style='color:gray;'>" + QString::number(time)
                  + " sec depuis départ</span><br>";

            previousLine = currentLine;
            totalTime = time;
        }

        html += "<hr><b>⏱️ Durée totale : " + QString::number(totalTime) + " sec</b>";

        resultText->setHtml(html);

    } catch (const std::string& err) {
        resultText->setText("❌ Erreur : " + QString::fromStdString(err));
    }
}
