#include "MapEditor.h"
#include "MapMenu.h"
#include "../../../Graphics/DrawingEnviroment.h"
#include "../../../Utils/textOperations.h"
#include "../../../Game.h"

MapEditor::MapEditor (float wdt, float hgt, std::string loadmap) :
	Menu(wdt, hgt, "mapeditor"),
	m_grid({12, 12, 1012, 512}, 8),
	m_drawer({12, 12, 1012, 512}, 2.f),
	m_mapname(loadmap), inputing(false),
	m_text(m_font, 15, sf::Color::White)
{
	if (m_mapname.empty())
		m_mapname = "untitled" + std::to_string(rand()), has_mapname = false;
	else
		m_drawer.LoadRects(m_mapname), has_mapname = true;
	
	m_toolnames = {
		{RectangleDrawer::State::Nothing,                     "None"},
		{RectangleDrawer::State::Deleting,                  "Delete"},
		{RectangleDrawer::State::Painting,                   "Paint"},
		{RectangleDrawer::State::Drawing,                     "Draw"},
		{RectangleDrawer::State::Moving,                      "Move"}, 
		{RectangleDrawer::State::Circular,     "Add Circular Motion"},
		{RectangleDrawer::State::Horizontal, "Add Horizontal Motion"}, 
		{RectangleDrawer::State::Vertical,     "Add Vertical Motion"},
	};
	
	m_text.setMaxChars(1000);
	m_text.setValue("ENTER MAP NAME");
}

void MapEditor::Select (Game & g) {
	if (current_option == 2) {
		if (!has_mapname) {
			inputing = true; return;
		}
		
		std::ofstream fout("../res/configuration-files/maps/" + m_mapname + ".conf");
		fout << m_drawer.GetRectsInfo(m_mapname);
		g.SetScene(new MapMenu(win_width, win_height));
	}
}

void MapEditor::ProcessEvent (sf::Event & e, Game & g) {
	m_drawer.ProcessEvents(e);
	if (inputing && m_text.processEvent(e, first_keystroke))
		if (first_keystroke) 
			first_keystroke = false;

	if (e.type != sf::Event::KeyPressed)
		return;
	
	if (inputing && e.key.code == sf::Keyboard::Enter) {
		if (!first_keystroke && !m_text.getString().isEmpty()) {
			inputing = false, has_mapname = !inputing; 
			m_mapname = m_text.getValue();
			current_option = 2;
			Select(g);
		}
	} else StandardMenuInput(g, e.key.code);
}

void MapEditor::Update (Game & g) {
	if (inputing) {
		m_text.update();
		m_texts[2].setString(m_text.getString());
		utils::center(m_texts[2], {win_width, win_height});
		return;
	}
	
	HighlightCurrentOption();
	std::string str = "Current Tool: " + m_toolnames[m_drawer.GetState()];
	m_texts[0].setString(str);
	utils::center(m_texts[0], {win_width, win_height});
}

void MapEditor::Render (DrawingEnviroment & drawEnv) {
	drawEnv.ClearWindow();
	m_drawer.Update(*drawEnv.getWin());
	m_grid.SnapToGrid(m_drawer);
	drawEnv.AddToLayer(&m_drawer, 2);
	drawEnv.AddToLayer(&m_grid, 1);
	
	for (auto &text : m_texts)
		drawEnv.AddToLayer(&text, 0);
	drawEnv.DrawAll();
}
