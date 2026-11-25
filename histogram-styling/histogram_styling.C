
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "TH1F.h"
#include "TF1.h"
#include "TRandom2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TColor.h"
#include "TSystem.h"

void histogram_styling()
{
    // STEP 1: Generate Gaussian data
    TRandom2 random(3);

    std::ofstream output("data.txt");
    output << std::setprecision(12);

    for (int i = 0; i < 1000; i++) {
        double value = random.Gaus(5, 1);
        output << value << std::endl;
    }

    output.close();

    // STEP 2: Read data from the file
    std::ifstream input("data.txt");
    std::vector<double> values;
    double value;

    if (!input.is_open()) {
        std::cerr << "Cannot open data.txt" << std::endl;
        return;
    }

    while (input >> value) {
        values.push_back(value);
    }

    input.close();

    // STEP 3: Create histogram
    TH1F *hist = new TH1F(
        "hist_styling", "Histogram", 100, 0, 10
    );

    for (double x : values) {
        hist->Fill(x);
    }

    hist->GetXaxis()->SetTitle("Distribution");
    hist->GetYaxis()->SetTitle("Entries");
    hist->SetStats(0);

    // STEP 4: Gaussian fitting
    TF1 *fit = new TF1("fit_styling", "gaus", 0, 10);
    fit->SetParameters(40, 5, 1);
    fit->SetLineColor(kRed);

    hist->Fit(fit, "RQN");

    // STEP 5: Create canvas and legend
    TCanvas *canvas = new TCanvas(
        "canvas_styling", "Histogram Styling", 900, 650
    );

    canvas->cd();
    hist->Draw("HIST");
    fit->Draw("SAME");

    TLegend *leg = new TLegend(0.6, 0.7, 0.9, 0.9);
    leg->AddEntry(hist, "Simulated Data", "l");
    leg->AddEntry(fit, "Gaussian Fit", "l");
    leg->Draw();

    gSystem->mkdir("outputs", kTRUE);

    // Helper: save current canvas
    auto save = [&](const char *name) {
        canvas->Modified();
        canvas->Update();

        std::string path = "outputs/";
        path += name;

        canvas->SaveAs(path.c_str());
    };

    save("01_original.png");

    // STEP 6: Add ticks on top and right
    canvas->SetTickx(1);
    canvas->SetTicky(1);

    save("02_ticks.png");

    // STEP 7: Move the legend
    leg->SetX1NDC(0.5);
    leg->SetY1NDC(0.6);
    leg->SetX2NDC(0.8);
    leg->SetY2NDC(0.8);

    save("03_legend_moved.png");

    // STEP 8: Expand the histogram range
    hist->SetBins(100, 0, 15);

    for (double x : values) {
        hist->Fill(x);
    }

    fit->SetRange(0, 15);
    fit->SetParameters(55, 5, 1);
    hist->Fit(fit, "RQN");

    canvas->cd();
    hist->Draw("HIST");
    fit->Draw("SAME");
    leg->Draw();

    save("04_wider_range.png");

    // STEP 9: Remove legend border
    leg->SetBorderSize(0);

    save("05_borderless_legend.png");

    // STEP 10: Bright green fill
    hist->SetFillColor(kGreen);

    save("06_bright_green.png");

    // STEP 11: Softer green fill
    hist->SetFillColor(kGreen - 9);

    save("07_soft_green.png");

    // STEP 12: Remove title and increase text sizes
    hist->SetTitle("");

    hist->GetXaxis()->SetTitleSize(0.05);
    hist->GetYaxis()->SetTitleSize(0.05);

    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);

    canvas->SetLeftMargin(0.14);
    canvas->SetBottomMargin(0.14);

    save("08_larger_text.png");

    // STEP 13: Show fill color in legend
    leg->Clear();
    leg->AddEntry(hist, "Simulated Data", "f");
    leg->AddEntry(fit, "Gaussian Fit", "l");
    leg->Draw();

    save("09_fill_legend.png");

    // STEP 14: Increase fit line thickness
    fit->SetLineWidth(3);

    save("10_thicker_fit.png");

    // STEP 15: Change the fit line to blue
    fit->SetLineColor(kBlue);
    fit->SetLineStyle(1);

    save("11_blue_solid_fit.png");

    // STEP 16: Try a red dotted line
    fit->SetLineColor(kRed);
    fit->SetLineStyle(3);

    save("12_dotted_red_fit.png");

    // STEP 17: Final dashed fit with grid
    fit->SetLineStyle(2);

    canvas->SetGridx(1);
    canvas->SetGridy(1);

    save("13_final_grid.png");

    // STEP 18: Print fitted results
    double mean = fit->GetParameter(1);
    double sigma = fit->GetParameter(2);

    std::cout << "\n--- FINAL RESULTS ---" << std::endl;
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

    std::cout << "\nAll 13 PNG files saved!"
              << std::endl;
}
