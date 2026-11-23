
#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TCanvas.h>

void grade_distribution()
{
    TH1F *hist1 = new TH1F(
        "hist1", "Histogram", 100, 0, 100
    );

    TH1F *hist2 = new TH1F(
        "hist2", "Histogram", 6, 1, 7
    );

    std::ifstream file("grades.txt");

    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open grades.txt"
                  << std::endl;
        return;
    }

    double value;

    while (file >> value)
    {
        hist1->Fill(value);
        hist2->Fill(value);
    }

    file.close();

    hist1->GetXaxis()->SetTitle("Grade");
    hist1->GetYaxis()->SetTitle("Entries");

    hist2->GetXaxis()->SetTitle("Grade");
    hist2->GetYaxis()->SetTitle("Entries");

    TCanvas *c1 = new TCanvas(
        "c1", "100 Bins", 800, 600
    );

    hist1->Draw();
    c1->SaveAs("outputs/01_grades_100_bins.png");

    TCanvas *c2 = new TCanvas(
        "c2", "6 Bins", 800, 600
    );

    hist2->Draw();
    c2->SaveAs("outputs/02_grades_6_bins.png");

    std::cout << "Entries: "
              << hist2->GetEntries() << std::endl;

    std::cout << "Mean: "
              << hist2->GetMean() << std::endl;

    std::cout << "Std Dev: "
              << hist2->GetStdDev() << std::endl;
}
