#ifndef COMMAND_H
#define COMMAND_H
class Command{
    public:
        virtual void execute()=0;
        virtual void undo()=0;
};

#endif

// place
// colourChange
// rotate
// move
// delete