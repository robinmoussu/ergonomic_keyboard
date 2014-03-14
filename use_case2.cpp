class Action {
    public:
        Action(const char* s);
        void operator+ (Event e);
};

Action set(Layer l);
Action latch(Layer l);
Action lock(Layer l);
Action unlock(Layer l);

class Event {
    public:
        void operator= (Action e);
}

class Key {
    public:
};

class Layer {
    public:
        Event operator[] (Key k);
        Action on_set;
        Action on_reset;
};

class Keyboard {
    public:
        void operator<< (Layer l);
};


Keyboard keyboard;
Layer alpha, shift, circum, shift_circum, ponctuation;
Key k_a, k_b, k_e, k_shift, k_circum, k_ponctuation;
Event none;

keyboard << alpha << shift << circum << shift_circum << ponctuation;

alpha[k_a] = "a";
alpha[k_b] = "b";
alpha[k_e] = "e";
alpha[k_shift] = set(shift);
alpha[k_circum] = latch(circum);
alpha[k_ponctuation] = set(ponctuation) + release_alone(",");
alpha[k_shift + k_circum] = shift_circum.set;

shift[k_a] = "A";
shift[k_b] = "B";
shift[k_e] = "E";

circum[k_a] = "â";
circum[k_e] = "ê";

shift_circum[k_a] = "Â";
shift_circum[k_e] = "Ê";

ponctuation[k_a] = ".";
