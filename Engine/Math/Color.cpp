#include "Color.h"

namespace rj {
	const Color Color::white(1, 1, 1);
	const Color Color::red(1, 0, 0);
	const Color Color::green(0, 1, 0);
	const Color Color::blue(0, 0, 1);
	const Color Color::purple(0.64f, 0, 1);
	const Color Color::cyan(0, 1, 1);
	const Color Color::orange(1, 0.5f, 0);
	const Color Color::black(0, 0, 0);
	const Color Color::yellow(1, 1, 0);

    std::istream& operator>>(std::istream& stream, Color& color)
    {
        std::string line;
        std::getline(stream, line);

        if (line.find("{") != std::string::npos)
        {
            std::string r = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
            color.r = std::stof(r);

            line = line.substr(line.find(",") + 1);

            std::string g = line.substr(0, line.find(","));
            color.g = stof(g);

            std::string b = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
            color.b = stof(b);
        }

        return stream;
    }
}