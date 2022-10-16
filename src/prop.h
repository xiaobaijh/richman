class base_prop {
public:
    base_prop();
    ~base_prop();
    enum prop_type { bomb,
                     doll,
                     barricade };
    int price;
    virtual void special_func(int position);
};

class bomp : base_prop {
    virtual void special_func(int position);
};

class doll : base_prop {
    virtual void special_func(int position);
};

class barricade : base_prop {
    virtual void special_func(int position);
};