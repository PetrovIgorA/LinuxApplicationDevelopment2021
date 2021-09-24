#include "file_window.h"

#include <locale>
#include <fstream>
#include <iostream>

FileWindow::FileWindow(const std::string& filename)
{
    std::setlocale(LC_ALL, "");
    initscr();
    if (ReadFile(filename)) {
        noecho();
        cbreak();
        // Create and initilize window
        window_high_ = LINES - 2 * DY;
        window_width_ = COLS - 2 * DX;
        // If window is too small then we will not draw file
        if (window_high_ > DY && window_width_ > DX) {
            mvprintw(0, 0, "File name: %s", filename.c_str());
            refresh();
            win_ = newwin(window_high_, window_width_, DY, DX);
            keypad(win_, true);
            scrollok(win_, true);
        }
        else {
            std::cerr << "Window is too small, file can't be draw" << std::endl;
        }
    }
}

bool FileWindow::ReadFile(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Can't open file " << filename << std::endl;
        return false;
    }
    std::string current_line;
    // Read input file
    while (std::getline(ifs, current_line)) {
        file_strings_.push_back(current_line);
    }
    ifs.close();
    return true;
}

void FileWindow::Draw()
{
    if (win_ == nullptr) {
        return;
    }
    int position_y = 0;
    int position_x = 0;
    do {
        // Clear window
        werase(win_);
        // Set lines in window
        for (int i = 0; i < window_high_ - DY && i + position_y < static_cast<int>(file_strings_.size()); ++i) {
            const auto& str_line = file_strings_[i + position_y];
            const char* line =
                position_x <= static_cast<int>(str_line.size()) ? str_line.c_str() + position_x : EMPTY_LINE;
            mvwprintw(win_, i + 1, 1, "%.120s", line);
        }
        // Set bounds in window
        box(win_, 0, 0);
        // Draw file
        wrefresh(win_);
    } while (KeyHandler(position_x, position_y));
}

bool FileWindow::KeyHandler(int& position_x, int& position_y)
{
    Keys key = static_cast<Keys>(wgetch(win_));
    switch (key) {
    case Keys::SPACE:
    case Keys::DOWN:
        position_y = std::min(position_y + 1, static_cast<int>(file_strings_.size()));
        break;
    case Keys::UP:
        position_y = std::max(0, position_y - 1);
        break;
    case Keys::RIGHT:
        position_x = std::min(position_x + 1, MAX_LINE_LENGTH);
        break;
    case Keys::LEFT:
        position_x = std::max(0, position_x - 1);
        break;
    case Keys::ESC:
        return false;
    default:
        break;
    }
    return true;
}

FileWindow::~FileWindow()
{
    endwin();
}
