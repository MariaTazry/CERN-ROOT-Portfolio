
#include "TRandom2.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TAxis.h"

#include <fstream>
#include <iostream>

void gaussian_distribution()
{
    // Generate 1000 Gaussian random values
    TRandom2 *rand = new TRandom2(3);

    std::ofstream file("gaussian_data.txt");

    if (!file.is_open()) {
        std::cout << "Cannot create data file!" << std::endl;
        return;
    }

    for (int i = 0; i < 1000; i++) {
        double r = rand->Gaus(5, 1);
        file << r << std::endl;
    }

    file.close();

    // Create histogram
    TH1F *hist = new TH1F(
        "hist", "Histogram", 100, 0, 10
    );

    // Read data from file
    std::ifstream input("gaussian_data.txt");

    if (!input.is_open()) {
        std::cout << "Cannot read data file!" << std::endl;
        return;
    }

    double value;

    while (input >> value) {
        hist->Fill(value);
    }

    input.close();

    // Set axis titles
    hist->GetXaxis()->SetTitle("Distribution");
    hist->GetYaxis()->SetTitle("Entries");

    // Create canvas
    TCanvas *c1 = new TCanvas(
        "c1", "Gaussian Distribution", 800, 600
    );

    // Save histogram without fit
    hist->Draw();
    c1->SaveAs("outputs/01_gaussian_histogram.png");

    // Perform Gaussian fit
    hist->Fit("gaus");

    c1->Modified();
    c1->Update();

    // Save histogram with Gaussian fit
    c1->SaveAs("outputs/02_gaussian_fit.png");
}
