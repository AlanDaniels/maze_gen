#include "common.hpp"
#include "random_strat.hpp"


// Calculate where to draw the maze sell.
ScreenCoord calc_offset(int w, int h)
{
    int x = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * w) + OUTER_BORDER_PIX;
    int y = ((CELL_SIZE_PIX + (CELL_BORDER_PIX - 1)) * h) + OUTER_BORDER_PIX;
    return ScreenCoord(x, y);
}


// And away we go.
int main()
{
    // Choose a random seed.
    // std::srand(std::time(0));

    // Fire up the display.
    cimg_library::CImg<uint8_t> image(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, NUM_CHANNELS, INITIAL_VALUE);
    cimg_library::CImgDisplay display(image, "Maze Generating");
    RandomStrategy strategy;

    // Display loop.
    bool first_draw = false;
    while (!display.is_closed()) {

        // Draw the maze cells.
        auto cells = strategy.getCells();
        for (auto it = cells.begin(); it != cells.end(); it++) {
            ScreenCoord coord = calc_offset(it->first.w, it->first.h);           
            if (it->second) {
            uint8_t dark_gray[] = { 0x40, 0x40, 0x40 };
                image.draw_rectangle(coord.x, coord.y, coord.x + CELL_SIZE_PIX, coord.y + CELL_SIZE_PIX, dark_gray);
            } else {
                uint8_t light_gray[] = { 0x80, 0x80, 0x80 };
                image.draw_rectangle(coord.x, coord.y, coord.x + CELL_SIZE_PIX, coord.y + CELL_SIZE_PIX, light_gray);
            }
        }

        // Draw the cell where the strategy is currently at. A bit of overdraw, but that's okay.
        {
            auto current = strategy.getCurrentCell();
            ScreenCoord coord = calc_offset(current.w, current.h);
            uint8_t red[] = { 0xFF, 0, 0 };
            image.draw_rectangle(coord.x, coord.y, coord.x + CELL_SIZE_PIX, coord.y + CELL_SIZE_PIX, red);
        }

        // Draw the connections.
        for (auto conn : strategy.getConnections()) {
            ScreenCoord begin_coord = calc_offset(conn.begin.w, conn.begin.h);
            ScreenCoord end_coord = calc_offset(conn.end.w, conn.end.h);

            int min_x = std::min(begin_coord.x, end_coord.x) + SQUISH_PIX;
            int max_x = std::max(begin_coord.x, end_coord.x) + CELL_SIZE_PIX - SQUISH_PIX;
            int min_y = std::min(begin_coord.y, end_coord.y) + SQUISH_PIX;
            int max_y = std::max(begin_coord.y, end_coord.y) + CELL_SIZE_PIX - SQUISH_PIX;

            uint8_t white[] = { 0xFF, 0xFF, 0xFF };
            image.draw_rectangle( min_x, min_y, max_x, max_y, white);
        }

        // Redraw every second.
        if (! first_draw) {
            display.wait();
            first_draw = true;
        } else {
            display.wait(250);
        }

        image.display(display);
        strategy.nextStep();
    }

    printf("All done!");
    return 0;
}
