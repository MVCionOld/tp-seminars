#ifndef SEMINAR_03_SINGLETON_H
#define SEMINAR_03_SINGLETON_H

class Singleton {
private:
    Singleton () {}
    Singleton (const Singleton&);
    Singleton& operator= (Singleton&);
public:
    static Singleton& GetInstance() {
        static Singleton instance;
        return instance;
    }
};

#endif //SEMINAR_03_SINGLETON_H
