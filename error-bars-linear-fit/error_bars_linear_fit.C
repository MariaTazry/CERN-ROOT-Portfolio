
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TColor.h>

#include <fstream>
#include <iostream>

void error_bars_linear_fit()
{
    // STEP 1: Create canvas
    TCanvas *c1 = new TCanvas(
        "c1", "Graph with Error Bars", 900, 600
    );

    // STEP 2: Create TGraphErrors
    TGraphErrors *gr = new TGraphErrors();

    // STEP 3: Open data file
    std::ifstream file("data3.txt");

    if (!file.is_open()) {
        std::cerr << "Cannot open data3.txt"
                  << std::endl;
        return;
    }

    // STEP 4: Read data and errors
    double x, y, ex, ey;

    while (file >> x >> y >> ex >> ey) {

        int n = gr->GetN();

        gr->SetPoint(n, x, y);
        gr->SetPointError(n, ex, ey);
    }

    file.close();

    if (gr->GetN() == 0) {
        std::cerr << "No valid data found!"
                  << std::endl;
        return;
    }

    // STEP 5: Graph appearance
    gr->SetTitle(
        "Linear Data with Error Bars;X;Y"
    );

    gr->SetMarkerStyle(3);
    gr->SetMarkerSize(1.3);
    gr->SetLineColor(kBlack);

    // STEP 6: Draw graph with error bars
    gr->Draw("AP");
    c1->SaveAs("outputs/01_error_bars.png");

    // STEP 7: Define linear fit function
    TF1 *fit = new TF1(
        "linear_fit", "pol1", 0, 5.5
    );

    fit->SetLineColor(kRed);
    fit->SetLineWidth(2);

    // STEP 8: Perform linear fitting
    gr->Fit(fit, "R");

    c1->Modified();
    c1->Update();

    // STEP 9: Save fitted graph
    c1->SaveAs("outputs/02_linear_fit.png");

    // STEP 10: Extract fitted parameters
    double intercept = fit->GetParameter(0);
    double slope = fit->GetParameter(1);

    // STEP 11: Print results
    std::cout << "\n--- LINEAR FIT RESULTS ---"
              << std::endl;

    std::cout << "Data points: "
              << gr->GetN() << std::endl;

    std::cout << "Intercept: "
              << intercept << std::endl;

    std::cout << "Slope: "
              << slope << std::endl;

    std::cout << "Chi-square: "
              << fit->GetChisquare() << std::endl;

    std::cout << "NDF: "
              << fit->GetNDF() << std::endl;

    std::cout << "\nBoth PNG files saved!"
              << std::endl;
}
