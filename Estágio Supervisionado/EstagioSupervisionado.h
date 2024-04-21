class Pia_Di{
    public:
    Pia_Di();
    ~Pia_Di();
    void push(int x, int y);
    void pop(int &x, int &y);
    bool vazio();
    bool cheio();
    bool print();
    private:
    struct StackNode{
        int x, y;
        StackNode *prox_endereco;    
    };
    typedef StackNode *prox_pont;
    prox_pont top;

};