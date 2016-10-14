#include <gtest/gtest.h>

#include "headerparser.hpp"

TEST(TestHeaderParser, SimpleCase)
{
    Utils::StringList_t lines{
        "#pragma once",
        "#include <qwt/qwt_plot_picker.h>",
        "class QwtPlotCanvas;",
        "namespace Stilla",
        "{",
        "    namespace Gui",
        "    {",
        "        class BasicPicker : public QwtPlotPicker",
        "        {",
        "            Q_OBJECT",
        "        public:",
        "            explicit BasicPicker(QWidget* canvas);",
        "            explicit BasicPicker(int xAxis, int yAxis, QWidget* canvas);",
        "            explicit BasicPicker(int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode,",
        "                                 QwtPlotCanvas* canvas);",
        "        signals:",
        "            void mouseMoved(const QPoint& pos) const;",
        "        protected:",
        "            virtual QwtText trackerText(const QPoint& pos) const override;",
        "        };",
        "    } // Gui",
        "} // Stilla"};
    HeaderParser p(lines);
    const auto res = p.run();
    EXPECT_EQ("BasicPicker", res.first);
    Utils::StringList_t expected_methods{
        "BasicPicker(QWidget* canvas)", "BasicPicker(int xAxis, int yAxis, QWidget* canvas)",
        "BasicPicker(int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas* canvas)",
        "void mouseMoved(const QPoint& pos) const", // TODO remove signals?
        "QwtText trackerText(const QPoint& pos) const"};
    EXPECT_EQ(expected_methods, res.second);
}