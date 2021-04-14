#include <stack>


struct Card {
    uint8_t value;
    bool is_opened;
};

class Pile {
public:
    std::stack<uint8_t> closed_pile; // вершина стека -- карта, которую откроют следующей
    uint8_t upper_value, lower_value; // стопки растут вниз (lower_value -- карта, на которую можно доложить карты)

    void Open_card() { // открыть карту (вызывать при условии, что открываемая карта в итоге откажется единственной в текущей стопке
        upper_value = closed_pile.pop();
        lower_value = upper_value;

        return;
    }

    bool Pile_is_done() {
        return ((upper_value - lower_value == 14 - 6) && (closed_pile.empty()));
    }
}

class Flop { // класс, описывабщий ситуацию на столе и позволяющий обращаться к стопкам
    std::vector<Pile> flop(8);

    std::vector<uint8_t> stat(); // для каждого достоинтва карты храним сколько есть закрытых карт такого же жостоинства

    std::set<uint8_t> need_as_bot(); // набор достоинств карт, которые требуются, чтобы их положить на стопки
    std::set<uint8_t> need_as_top(); // набор достоинств карт, которые требуются, чтобы на них положить стопки

    bool find_best_donor_pile(uint8_t recipient_pile, uint8_t& donor_pile) {
        donor_pile = recipient_pile;
        for (int i = 0; i < 8; ++i) {
            if (pecipient_pile != i) {  
                if (flop[i].upper_value == flop[recipient_pile].lower_value) { // можем положить i-ую стопку на нашу стопку
                    donor_pile = i; // нашли, какую стопку можно положить на текущую

                    uint8_t applicant = flop[i].closed_pile.top(); // чекаем, хорошая ли карта откроется, если переложить i-ую стопку
                    if ((need_as_bot.count(applicant) > 1) || (need_as_top.count(applicant) > 1)) { // даже если плохой случай, есть еще одино применение открышейся карте
                        return true;
                    } 
                    if ((need_as_bot.count(applicant) == 1) && (applicant != flop[recipient_pile].lower_value)) { // исключаем проблему "затирания" доступного места, чтобы положить открывшуюся карту, стопкой, которую только что сняли
                        return true;
                    }
                    if ((need_as_top.count(applicant) == 1) && (applicant != flop[i].upper_value)) { // исключаем когда хотим снять и положить туда же
                        return true;
                    }
                }
            }
        }
        return false; // не нашли стопку, которая открыла бы полезную карту
    }
} 


