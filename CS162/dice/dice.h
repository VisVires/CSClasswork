#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

class Dice
{
    public:
        Dice();
        Dice(int numSides);
        ~Dice(){};
        virtual int rollDice() const;
        void setNumSides(int numSides);

    protected:
        int numSides;
};

class LoadedDice:public Dice
{
    private:

    public:
        LoadedDice();
        LoadedDice(int numSides);
        ~LoadedDice(){};
        virtual int rollDice() const;

};
#endif // DICE_H_INCLUDED
