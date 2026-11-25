
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TRandom2.h"
#include "TLegend.h"

void histogram_legend()
{
    // STEP 1: Generate Gaussian data
    TRandom2 random(3);

    std::ofstream output("data.txt");

    if (!output.is_open()) {
        std::cerr << "Cannot create data.txt" << std::endl;
        return;
    }

    for (int i = 0; i < 1000; i++) {
        double value = random.Gaus(5, 1);
        output << value << std::endl;
    }

    output.close();

    // STEP 2: Read data into a histogram
    TH1F *hist = new TH1F(
        "hist_legend",
        "Histogram;Distribution;Entries",
        100, 0, 10
    );

    std::ifstream input("data.txt");

    if (!input.is_open()) {
        std::cerr << "Cannot open data.txt" << std::endl;
        return;
    }

    double value;

    while (input >> value) {
        hist->Fill(value);
    }

    input.close();

    hist->SetLineColor(kBlue);
    hist->SetStats(1);

    // STEP 3: Define and fit Gaussian function
    TF1 *fit = new TF1(
        "gaussian_fit",
        "gaus",
        0, 10
    );

    fit->SetParameters(40, 5, 1);
    fit->SetLineColor(kRed);
    fit->SetLineWidth(2);

    hist->Fit(fit, "RQN");

    TCanvas *canvas = new TCanvas(
        "canvas_legend",
        "Histogram Legend Tutorial",
        800, 600
    );

    // OUTPUT 1: Histogram with Gaussian fit
    hist->Draw("HIST");
    fit->Draw("SAME");

    canvas->SaveAs("outputs/01_before_legend.png");

    // OUTPUT 2: Add an empty legend
    canvas->Clear();

    hist->Draw("HIST");
    fit->Draw("SAME");

    TLegend *emptyLegend = new TLegend(
        0.7, 0.7, 0.9, 0.9
    );

    emptyLegend->Draw();

    canvas->SaveAs("outputs/02_empty_legend.png");

    // OUTPUT 3: Add legend entries
    canvas->Clear();

    hist->Draw("HIST");
    fit->Draw("SAME");

    TLegend *legend1 = new TLegend(
        0.7, 0.7, 0.9, 0.9
    );

    legend1->AddEntry(hist, "Measured Data", "l");
    legend1->AddEntry(fit, "Fit Function", "l");
    legend1->Draw();

    canvas->SaveAs("outputs/03_legend_with_labels.png");

    // OUTPUT 4: Change legend position
    canvas->Clear();

    hist->Draw("HIST");
    fit->Draw("SAME");

    TLegend *legend2 = new TLegend(
        0.6, 0.7, 0.9, 0.9
    );

    legend2->AddEntry(hist, "Measured Data", "l");
    legend2->AddEntry(fit, "Fit Function", "l");
    legend2->Draw();

    canvas->SaveAs("outputs/04_wider_legend.png");

    // OUTPUT 5: Remove statistics box
    canvas->Clear();

    hist->SetStats(0);

    hist->Draw("HIST");
    fit->Draw("SAME");

    TLegend *finalLegend = new TLegend(
        0.6, 0.7, 0.9, 0.9
    );

    finalLegend->AddEntry(hist, "Measured Data", "l");
    finalLegend->AddEntry(fit, "Fit Function", "l");
    finalLegend->Draw();

    canvas->SaveAs("outputs/05_final_legend.png");

    // STEP 4: Print fit results
    double mean = fit->GetParameter(1);
    double sigma = fit->GetParameter(2);

    std::cout << "Entries: " << hist->GetEntries()
              << std::endl;

    std::cout << "Fitted Mean: " << mean
              << std::endl;

    std::cout << "Fitted Sigma: " << sigma
              << std::endl;

    if (sigma != 0) {
        std::cout << "Mean / Sigma: "
                  << mean / sigma << std::endl;
    }

    std::cout << "All five PNG files saved!"
              << std::endl;
}
