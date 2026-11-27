
#include <TCanvas.h>
#include <TF1.h>
#include <TMath.h>
#include <TColor.h>
#include <iostream>

void user_defined_functions()
{
    // Create a canvas
    TCanvas *c1 = new TCanvas(
        "c1", "User Defined Functions", 900, 600
    );

    // =========================================
    // PART 1: Linear function without parameters
    // =========================================

    TF1 *linear = new TF1(
        "linear", "[0]+[1]*x", 0, 5
    );

    linear->SetLineColor(kRed);
    linear->Draw();

    c1->Modified();
    c1->Update();
    c1->SaveAs("outputs/01_before_parameters.png");


    // =========================================
    // PART 2: Set parameters for the linear function
    // =========================================

    linear->SetParameter(0, 1);
    linear->SetParameter(1, 2);

    linear->SetTitle("Linear Function;X;f(x)");
    linear->Draw();

    c1->Modified();
    c1->Update();
    c1->SaveAs("outputs/02_linear_function.png");


    // =========================================
    // PART 3: Exponentially damped sine function
    // =========================================

    TF1 *damped = new TF1(
        "damped",
        "exp(-[1]*x)*[0]*sin(x)",
        0,
        10*TMath::Pi()
    );

    damped->SetParameter(0, 1);
    damped->SetParameter(1, 0.1);

    damped->SetLineColor(kRed);
    damped->SetNpx(1000);
    damped->Draw();

    c1->Modified();
    c1->Update();
    c1->SaveAs("outputs/03_damped_sine.png");


    // =========================================
    // PART 4: Remove the function title
    // =========================================

    damped->SetTitle(";X;f(x)");
    damped->Draw();

    c1->Modified();
    c1->Update();
    c1->SaveAs("outputs/04_damped_sine_no_title.png");


    // =========================================
    // Final information
    // =========================================

    std::cout << "All four PNG files saved!"
              << std::endl;
}
