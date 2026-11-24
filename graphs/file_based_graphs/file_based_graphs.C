
#include <iostream>
#include <fstream>
#include <string>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TColor.h>

// Read X-Y data and save a graph
void save_graph(const char* input_file,
                const char* output_file,
                bool red_line,
                bool axis_titles,
                bool graph_title)
{
    std::ifstream file(input_file);

    if (!file.is_open())
    {
        std::cerr << "Cannot open: "
                  << input_file << std::endl;
        return;
    }

    TGraph gr;

    double x, y;

    // Read both columns from the data file
    while (file >> x >> y)
    {
        gr.SetPoint(gr.GetN(), x, y);
    }

    file.close();

    if (gr.GetN() == 0)
    {
        std::cerr << "No valid data found."
                  << std::endl;
        return;
    }

    // Marker settings
    gr.SetMarkerStyle(kFullCircle);
    gr.SetMarkerSize(1);

    // Line settings
    gr.SetLineWidth(red_line ? 2 : 1);
    gr.SetLineColor(red_line ? kRed : kBlack);

    // Graph title
    if (graph_title)
    {
        gr.SetTitle("Graph");
    }
    else
    {
        gr.SetTitle("");
    }

    // Create a unique canvas
    static int canvas_number = 0;
    std::string canvas_name =
        "canvas_" + std::to_string(++canvas_number);

    TCanvas canvas(
        canvas_name.c_str(),
        "ROOT Graph",
        800, 600
    );

    // Draw axes, line and points
    gr.Draw("ALP");

    // Axis titles
    if (axis_titles)
    {
        gr.GetXaxis()->SetTitle("X Values");
        gr.GetYaxis()->SetTitle("Y Values");
    }

    canvas.Modified();
    canvas.Update();

    // Save the PNG file
    canvas.SaveAs(output_file);

    std::cout << "Saved: "
              << output_file << std::endl;
}

// Main ROOT function
void file_based_graphs()
{
    // 1. Original quadratic graph
    save_graph(
        "data_quadratic.txt",
        "outputs/01_quadratic_graph.png",
        false, false, false
    );

    // 2. Modified data with Y = 100
    save_graph(
        "data_modified.txt",
        "outputs/02_modified_data_graph.png",
        false, false, false
    );

    // 3. Red line and circular markers
    save_graph(
        "data_modified.txt",
        "outputs/03_red_line_graph.png",
        true, false, false
    );

    // 4. Add X and Y axis titles
    save_graph(
        "data_modified.txt",
        "outputs/04_axis_titles_graph.png",
        true, true, false
    );

    // 5. Final styled graph with title
    save_graph(
        "data_modified.txt",
        "outputs/05_final_graph.png",
        true, true, true
    );
}
