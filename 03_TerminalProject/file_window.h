#ifndef FILE_WINDOW_H_
#define FILE_WINDOW_H_

#include <string>
#include <vector>

#include <ncurses.h>

enum class Keys : int
{
    UP = KEY_UP,
    DOWN = KEY_DOWN,
    RIGHT = KEY_RIGHT,
    LEFT = KEY_LEFT,
    ESC = 27,
    SPACE = 0x20
};

class FileWindow
{
public:
    explicit FileWindow(const std::string& filename);
    FileWindow(const FileWindow& other) = delete;
    FileWindow(FileWindow&& other) = delete;

    void Draw();

    ~FileWindow();

private:
    static constexpr const char* EMPTY_LINE = "";
    static constexpr int DX = 2;
    static constexpr int DY = 2;
    static constexpr int MAX_LINE_LENGTH = 120;

    [[nodiscard]] bool ReadFile(const std::string& filename);
    [[nodiscard]] bool KeyHandler(int& position_x, int& position_y);

    int window_high_ = 0;
    int window_width_ = 0;
    std::vector<std::string> file_strings_;
    WINDOW* win_ = nullptr;
};

#endif // FILE_WINDOW_H_
