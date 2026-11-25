
#include <TRandom2.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>

#include <fstream>
#include <iomanip>
#include <iostream>

void gaussian_fitting()
{
    // Step 1: Generate Gaussian random data
    TRandom2 generator(3);

    std::ofstream out("data.txt");

    if (!out.is_open()) {
        std::cerr << "Cannot create data.txt" << std::endl;
        return;
    }

    out << std::setprecision(12);

    for (int i = 0; i < 1000; i++) {
        double r = generator.Gaus(5, 1);
        out << r << std::endl;
    }

    out.close();

    // Step 2: Read data into a histogram
    TH1F original(
        "original",
        "Gaussian Distribution;Distribution;Entries",
        100, 0, 10
    );

    std::ifstream input("data.txt");

    if (!input.is_open()) {
        std::cerr << "Cannot open data.txt" << std::endl;
        return;
    }

    double value;

    while (input >> value) {
        original.Fill(value);
    }

    input.close();

    TCanvas canvas("canvas", "Gaussian Fitting", 900, 600);

    // Step 3: Histogram without fitting
    original.Draw();
    canvas.SaveAs("outputs/01_before_fit.png");

    // Step 4: ROOT built-in Gaussian fit
    TH1F *hist1 = (TH1F*)original.Clone("hist1");

    canvas.Clear();
    hist1->Draw();
    hist1->Fit("gaus");

    canvas.SaveAs("outputs/02_builtin_gaussian_fit.png");

    // Step 5: User-defined TF1, range 0 to 10
    TH1F *hist2 = (TH1F*)original.Clone("hist2");

    TF1 fit_full("fit_full", "gaus", 0, 10);

    fit_full.SetParameters(40, 5, 1);

    canvas.Clear();
    hist2->Draw();
    hist2->Fit(&fit_full, "RB");

    canvas.SaveAs("outputs/03_full_range_fit.png");

    // Step 6: Restricted fitting range 4 to 6
    TH1F *hist3 = (TH1F*)original.Clone("hist3");

    TF1 fit_range("fit_range", "gaus", 4, 6);

    fit_range.SetParameters(40, 5, 1);

    canvas.Clear();
    hist3->Draw();
    hist3->Fit(&fit_range, "RB");

    canvas.SaveAs("outputs/04_restricted_range_fit.png");

    // Step 7: Final fit with initial parameters
    TH1F *hist4 = (TH1F*)original.Clone("hist4");

    TF1 fit_final("fit_final", "gaus", 0, 10);

    fit_final.SetParameter(0, 40);
    fit_final.SetParameter(1, 5);
    fit_final.SetParameter(2, 1);

    canvas.Clear();
    hist4->Draw();

    int status = hist4->Fit(&fit_final, "RB");

    canvas.SaveAs("outputs/05_final_gaussian_fit.png");

    // Step 8: Extract fitted parameters
    if (status == 0) {
        double mean = fit_final.GetParameter(1);
        double sigma = fit_final.GetParameter(2);

        std::cout << "\n--- FINAL FIT RESULTS ---\n";
        std::cout << "Entries: " << hist4->GetEntries() << std::endl;
        std::cout << "Fitted Mean: " << mean << std::endl;
        std::cout << "Fitted Sigma: " << sigma << std::endl;

        if (sigma != 0) {
            std::cout << "Mean / Sigma: "
                      << mean / sigma << std::endl;
        }
    } else {
        std::cout << "Final fit did not converge successfully."
                  << std::endl;
    }

    std::cout << "\nAll five PNG files saved!" << std::endl;
}
