#include <SFML/Graphics.hpp>
#include <cstdlib>   // for std::rand, std::srand
#include <ctime>     // for std::time
#include <iostream>

// توليد لون عشوائي
sf::Color randomColor() {
    return sf::Color(static_cast<sf::Uint8>(std::rand() % 256),
                     static_cast<sf::Uint8>(std::rand() % 256),
                     static_cast<sf::Uint8>(std::rand() % 256));
}

int main() {
    // نافذة اللعبة
    const unsigned int WINDOW_W = 800;
    const unsigned int WINDOW_H = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Bouncing Ball - Youssef");

    // تهيئة العشوائية
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // كرة
    const float radius = 20.f;
    sf::CircleShape ball(radius);
    ball.setOrigin(radius, radius); // نخلي الإسناد في المركز علشان الحركة أسهل
    ball.setPosition(WINDOW_W / 2.f, WINDOW_H / 2.f);
    ball.setFillColor(randomColor());

    // سرعة الحركة (بيكسل / ثانية)
    sf::Vector2f velocity(200.f, 150.f); // تقدر تغيّر القيم دي علشان تبطّء أو تسرّع الكرة

    // مؤقت للـ delta time
    sf::Clock clock;

    while (window.isOpen()) {
        // حدث/مدخلات
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            // بزر الماوس تعيد اختيار لون جديد (اختياري للتفاعل)
            if (event.type == sf::Event::MouseButtonPressed) {
                ball.setFillColor(randomColor());
            }
        }

        // حساب delta time
        float dt = clock.restart().asSeconds();

        // تحديث موقع الكرة
        sf::Vector2f pos = ball.getPosition();
        pos += velocity * dt;
        ball.setPosition(pos);

        // كشف التصادم مع الحواف + انعكاس + تغيير اللون عند المس
        bool hit = false;
        // الجدار الأيسر
        if (pos.x - radius <= 0.f) {
            pos.x = radius;
            velocity.x = -velocity.x;
            hit = true;
        }
        // الجدار الأيمن
        else if (pos.x + radius >= WINDOW_W) {
            pos.x = WINDOW_W - radius;
            velocity.x = -velocity.x;
            hit = true;
        }
        // الجدار العلوي
        if (pos.y - radius <= 0.f) {
            pos.y = radius;
            velocity.y = -velocity.y;
            hit = true;
        }
        // الجدار السفلي
        else if (pos.y + radius >= WINDOW_H) {
            pos.y = WINDOW_H - radius;
            velocity.y = -velocity.y;
            hit = true;
        }

        if (hit) {
            ball.setPosition(pos);           // نضمن وضع الكرة بعد التصادم
            ball.setFillColor(randomColor()); // نغيّر لون الكرة عند ملامسة أي جدار
        }

        // رسم
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.display();
    }

    return 0;
}
