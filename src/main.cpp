#include <QApplication>
#include <QDebug>  // Pour qDebug()
#include <filesystem>  // Pour std::filesystem
#include "mainwindow.h"
#include "Projet.hpp"

travel::Projet projet;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    
    if (!std::filesystem::exists("data/s.csv"))
        qDebug() << "❌ Fichier stations.csv introuvable";

    if (!std::filesystem::exists("data/c.csv"))
        qDebug() << "❌ Fichier aretes.csv introuvable";

    
    projet.read_stations("data/s.csv");
    projet.read_connections("data/c.csv");

    
    MainWindow window;
    window.show();

    return app.exec();
}