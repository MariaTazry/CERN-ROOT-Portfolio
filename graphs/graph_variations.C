
#include <TGraph.h>
#include <TCanvas.h>
#include <TAttMarker.h>

void save_graph(const char *filename, int markerStyle,
                double markerSize, const char *drawOption)
{
    double x[5] = {1, 2, 3, 4, 5};
    double y[5] = {1, 4, 9, 16, 25};

    TGraph gr(5, x, y);

    TCanvas c("c", "Graph", 800, 600);

    gr.SetTitle("Graph");
    gr.SetMarkerStyle(markerStyle);
    gr.SetMarkerSize(markerSize);

    gr.Draw(drawOption);

    c.Modified();
    c.Update();
    c.SaveAs(filename);
}

void graph_variations()
{
    save_graph("outputs/01_line_graph.png",
               1, 1, "AL");

    save_graph("outputs/02_style4.png",
               4, 1, "ACP");

    save_graph("outputs/03_style3.png",
               3, 1, "ACP");

    save_graph("outputs/04_style2.png",
               2, 1, "ACP");

    save_graph("outputs/05_style5_big.png",
               5, 5, "ACP");

    save_graph("outputs/06_open_circle.png",
               kOpenCircle, 5, "ACP");

    save_graph("outputs/07_full_circle.png",
               kFullCircle, 5, "ACP");
}
