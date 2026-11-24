
#include <TRandom2.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <iostream>

void uniform_random_distribution()
{
    // 1. Random number generator with a fixed seed
    TRandom2 random(1);

    std::cout << "First three random numbers:" << std::endl;

    TRandom2 preview(1);
    for (int i = 0; i < 3; i++) {
        std::cout << preview.Rndm() << std::endl;
    }

    // 2. Histograms with different numbers of entries and bins
    TH1F *hist1 = new TH1F(
        "hist1", "Uniform Distribution - 1000 Events",
        100, 0, 100
    );

    TH1F *hist2 = new TH1F(
        "hist2", "Uniform Distribution - 10000 Events",
        100, 0, 100
    );

    TH1F *hist3 = new TH1F(
        "hist3", "Uniform Distribution - 25 Bins",
        25, 0, 100
    );

    // 3. Generate 10000 uniformly distributed random values
    for (int i = 0; i < 10000; i++) {
        double r = random.Rndm() * 100;

        if (i < 1000) {
            hist1->Fill(r);
        }

        hist2->Fill(r);
        hist3->Fill(r);
    }

    // 4. Histogram 1: 1000 events, 100 bins
    TCanvas *c1 = new TCanvas("c1", "1000 Events", 800, 600);
    hist1->Draw();
    c1->SaveAs("outputs/01_uniform_1000.png");

    // 5. Histogram 2: 10000 events, 100 bins
    TCanvas *c2 = new TCanvas("c2", "10000 Events", 800, 600);
    hist2->Draw();
    c2->SaveAs("outputs/02_uniform_10000.png");

    // 6. Histogram 3: Y-axis range from 0 to 200
    TCanvas *c3 = new TCanvas("c3", "Y Axis Range", 800, 600);
    hist2->GetYaxis()->SetRangeUser(0, 200);
    hist2->Draw();
    c3->SaveAs("outputs/03_uniform_y_range.png");

    // 7. Histogram 4: 25 bins, Y-axis range 0 to 1000
    TCanvas *c4 = new TCanvas("c4", "25 Bins", 800, 600);
    hist3->GetYaxis()->SetRangeUser(0, 1000);
    hist3->Draw();
    c4->SaveAs("outputs/04_uniform_25_bins.png");

    std::cout << "All four histograms saved successfully!"
              << std::endl;
}
