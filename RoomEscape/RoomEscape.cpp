#include <bangtal>
using namespace bangtal;

int main()
{
	auto scene1 = Scene::create("룸1", "Images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Images/배경-2.png");

	auto key = Object::create("Images/열쇠.png", scene2, 600, 150);
	key->setScale(.2f);
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		object->pick();
		return true;
		});

	auto ladder = Object::create("Images/사다리.png", scene1, 750, 250);
	ladder->setScale(.2f);
	ladder->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		object->pick();
		return true;
		});

	auto flowerpot_moved = false;
	auto flowerpot = Object::create("Images/화분.png", scene2, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (!flowerpot_moved) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				object->locate(scene1, 450, 150);
				flowerpot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				object->locate(scene1, 650, 150);
				flowerpot_moved = true;
			}
		}
		return true;
		});

	auto open1 = false;
	auto door1 = Object::create("Images/바닥-문-닫힘.png", scene1, 550, 100);
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open1 == false) {
			if (ladder->isHanded()) {
				object->setImage("Images/바닥-문-열림.png");
				open1 = true;
			}
			else {
				showMessage("사다리가 있어야 내려갈 수 있어");
			}
		}
		else {
			scene2->enter();
		}
		
		return true;
		});

	auto open2 = false;
	auto door2 = Object::create("Images/문-오른쪽-닫힘.png", scene2, 800, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open2 == false) {
			if (key->isHanded()) {
				object->setImage("Images/문-오른쪽-열림.png");
				open2 = true;
			}
			else {
				showMessage("열쇠가 필요해!!!");
			}
		}
		else {
			endGame();
		}
		return true;
		});


	// startGame(장면)으로 게임을 시작한다.
	startGame(scene1);

	return 0;
}
