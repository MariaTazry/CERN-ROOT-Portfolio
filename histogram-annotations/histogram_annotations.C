
#include <iostream>
#include <fstream>
#include <iomanip>

#include <TH1F.h>
#include <TRandom2.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLine.h>
#include <TArrow.h>
#include <TLatex.h>
#include <TSystem.h>
#include <TColor.h>
#include <TAxis.h>

void histogram_annotations()
{
    // Create output directory
    gSystem->mkdir("outputs", true);

    // STEP 1: Generate Gaussian data
    TRandom2 random(3);

    std::ofstream file("data.txt");

    if (!file.is_open()) {
        std::cout << "Error creating data.txt" << std::endl;
        return;
    }

    file << std::setprecision(12);

    for (int i = 0; i < 1000; i++) {
        double value = random.Gaus(5, 1);
        file << value << std::endl;
    }

    file.close();

    // STEP 2: Create histogram
    TH1F *hist = new TH1F(
        "hist", "", 100, 0, 15
    );

    std::ifstream input("data.txt");

    if (!input.is_open()) {
        std::cout << "Error opening data.txt" << std::endl;
        return;
    }

    double value;

    while (input >> value) {
        hist->Fill(value);
    }

    input.close();

    // STEP 3: Histogram styling
    hist->SetFillColor(kGreen - 9);
    hist->SetLineColor(kBlack);
    hist->SetStats(0);

    hist->GetXaxis()->SetTitle("Distribution");
    hist->GetYaxis()->SetTitle("Entries");

    hist->GetXaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetTitleSize(0.05);

    hist->GetXaxis()->SetLabelSize(0.045);
    hist->GetYaxis()->SetLabelSize(0.045);

    // STEP 4: Define Gaussian fit
    TF1 *fit = new TF1("fit", "gaus", 0, 15);

    fit->SetParameters(40, 5, 1);
    fit->SetLineColor(kRed + 1);
    fit->SetLineWidth(3);
    fit->SetLineStyle(2);
    fit->SetNpx(500);

    // STEP 5: Create canvas
    TCanvas *c1 = new TCanvas(
        "c1", "Histogram Annotations", 900, 650
    );

    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();

    // Fit the data
    hist->Fit(fit, "RQ0");

    hist->Draw("HIST");
    fit->Draw("SAME");

    // STEP 6: Add legend
    TLegend *leg = new TLegend(
        0.60, 0.70, 0.87, 0.87
    );

    leg->SetBorderSize(0);
    leg->SetFillStyle(0);

    leg->AddEntry(hist, "Simulated Data", "f");
    leg->AddEntry(fit, "Gaussian Fit", "l");

    leg->Draw();

    // SAVE 1: Original styled histogram
    c1->Modified();
    c1->Update();
    c1->Print("outputs/01_original_histogram.png");

    // STEP 7: Add horizontal reference line
    TLine *line = new TLine(0, 20, 15, 20);

    line->SetLineWidth(2);
    line->SetLineColor(kOrange + 1);
    line->Draw();

    // SAVE 2: Histogram with line
    c1->Modified();
    c1->Update();
    c1->Print("outputs/02_horizontal_line.png");

    // STEP 8: Find the histogram bin
    double x0 = 6.3;

    int bin = hist->FindBin(x0);

    double y0 = hist->GetBinContent(bin);

    // STEP 9: Create arrow
    TArrow *arrow = new TArrow(
        10, 30, x0, y0, 0.02, ">"
    );

    arrow->SetLineWidth(2);
    arrow->SetArrowSize(0.02);
    arrow->SetLineColor(kBlue);
    arrow->SetFillColor(kBlue);

    arrow->Draw();

    // SAVE 3: Histogram with arrow
    c1->Modified();
    c1->Update();
    c1->Print("outputs/03_arrow_annotation.png");

    // STEP 10: Add text using TLatex
    TLatex *text = new TLatex(
        10, 30, "Important Point"
    );

    text->SetTextSize(0.035);
    text->SetTextColor(kBlack);

    text->Draw();

    // SAVE 4: Final annotated histogram
    c1->Modified();
    c1->Update();
    c1->Print("outputs/04_final_annotated_histogram.png");

    // STEP 11: Print results
    double mean = fit->GetParameter(1);
    double sigma = fit->GetParameter(2);

    std::cout << "\n--- FINAL RESULTS ---" << std::endl;

    std::cout << "Entries: "
              << hist->GetEntries() << std::endl;

    std::cout << "Fitted Mean: "
              << mean << std::endl;

    std::cout << "Fitted Sigma: "
              << sigma << std::endl;

    if (sigma != 0) {
        std::cout << "Mean / Sigma: "
                  << mean / sigma << std::endl;
    }

    std::cout << "Highlighted bin: "
              << bin << std::endl;

    std::cout << "Bin content: "
              << y0 << std::endl;

    std::cout << "\nAll four PNG files saved!"
              << std::endl;
}