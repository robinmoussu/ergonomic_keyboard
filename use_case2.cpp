#include <initializer_list>
using namespace std;

class Action {
    public:
        Action(const char* s);
        void operator+ (Action e);

        static Action none();
};

class Event {
    public:
        static Event none();
};

class Signal {
    public:
        void operator= (Action const& a);
};

class Key {
    public:
        operator Event ();
        Event operator+ (Key k);
        Event release();
        Event release_alone();
        Event on_press_ms(int ms);
        Event on_multiple_press(int nb_press);
};

class Layer;
class Layer_group {
    public:
        Layer_group operator<< (Layer const& l); // add a layer with higher priority
};

class Layer {
    public:
        Layer_group operator<< (Layer const& l); // create a group layer with current layer at lower priority
        void operator= (Layer const& l);
        void operator= (char const* s);
        Signal operator[] (Event e);
        Signal on_set();
        Signal on_reset();

        Action set();
        Action latch();
        Action lock();
        Action unlock();
};

class Led {
    public:
};

class Group_led {
    public:
        void operator= (initializer_list<Led> l);
};

class Keyboard {
    public:
        void operator= (Layer_group const l);  // clear layer and define used layer
        Keyboard(int nb_raw, int nb_collumn);
        void operator= (initializer_list<Key> k); // define key position on matrice
        Group_led led;
};

int main (void)
{
    Keyboard keyboard(2,3);                                 // A keyboard of 2*3 touches
    Layer alpha, shift, circum, shift_circum, ponctuation;  // The diferents layers
    Key k_a, k_b, k_e, k_shift, k_circum, k_ponctuation;    // The keys of the keyboard
    Led l_shift;                                            // Lock indicators

    // keyboard configuration : Layer and position of the keys
    keyboard     = alpha << shift << circum << shift_circum << ponctuation;
    keyboard     = { k_a,     k_b,      k_e,
                     k_shift, k_circum, k_ponctuation };
    keyboard.led = { l_shift };

    // alphabetic layer
    alpha[k_a] = "a";
    alpha[k_b] = "b";
    alpha[k_e] = "e";
    // specials keys and more complicated event (on alpha layer)
    alpha[k_shift]                       = shift.set();
    alpha[k_shift.on_multiple_press(3)]  = shift.lock();
    alpha[k_circum]                      = circum.latch();
    alpha[k_ponctuation]                 = ponctuation.set();
    alpha[k_ponctuation.release_alone()] = ",";
    alpha[k_shift + k_circum]            = shift_circum.set();
    alpha[k_shift.on_press_ms(50)]       = "$<esc>";

    // shift layer
    shift[k_a] = "A";
    shift[k_b] = "B";
    shift[k_e] = "E";

    // circum layer
    circum[k_a] = "â";
    circum[k_e] = "ê";

    // shift + circum layer
    shift_circum[k_a] = "Â";
    shift_circum[k_e] = "Ê";

    // ponctuation layer
    ponctuation[k_a] = ".";
}

