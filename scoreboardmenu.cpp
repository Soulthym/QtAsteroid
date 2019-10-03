#include "scoreboardmenu.h"

ScoreBoardMenu::ScoreBoardMenu(QWidget *parent) : QWidget(parent)
{
    topLayout = new QVBoxLayout();
    subLayout = new QHBoxLayout();

    this->setLayout(topLayout);
    topLayout->addLayout(subLayout);

    table = new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    subLayout->addWidget(table);
    this->loadCsv("./scores.csv", table);
}

void ScoreBoardMenu::loadCsv(char *filename, QTableWidget *table) {
    table->setRowCount(10);
    table->setColumnCount(2);
    QFile inputFile(filename);
    int rowCount = 0;
    int maxRowCount = 0;
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while (!in.atEnd())
        {
            QStringList line = in.readLine().split(',');
            table->setRowCount(++rowCount);
            maxRowCount = std::max(maxRowCount, line.size());
            table->setColumnCount(maxRowCount);
            int column = 0;
            for ( const auto& item : line) {
                table->setItem(rowCount-1, column++, new QTableWidgetItem(item));
            }
        }
        inputFile.close();
    }
}
