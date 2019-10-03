#include "scoreboardmenu.h"

ScoreBoardMenu::ScoreBoardMenu(QWidget *parent) : QWidget(parent) {
    scoreFilename = "./scores.csv";
    topLayout = new QVBoxLayout();
    buttonPanel = new QHBoxLayout();

    setLayout(topLayout);

    table = new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    topLayout->addWidget(table);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    loadCsv(scoreFilename, table);

    exitButton = new QPushButton("Back to Menu");
    clearButton = new QPushButton("Clear ScoreBoard");
    topLayout->addLayout(buttonPanel);
    buttonPanel->addWidget(exitButton);
    buttonPanel->addWidget(clearButton);
	connect(clearButton, SIGNAL(clicked()), this, SLOT(clearCsv()));
}

void ScoreBoardMenu::loadCsv(const QString filename, QTableWidget *table) {
    table->setRowCount(0);
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
    table->setHorizontalHeaderLabels({"Player","Score"});
}

void ScoreBoardMenu::backToMenu(const QObject *receiver, const char *slotMemberFunction) {
	connect(exitButton, SIGNAL(pressed()), receiver, slotMemberFunction);
}

void ScoreBoardMenu::clearCsv() {
    QFile csvFile(scoreFilename);
    csvFile.remove();
}
