//
// Created by RH on 20/09/2019.
//

#ifndef OPENBROODCRAFT_COMMAND_H
#define OPENBROODCRAFT_COMMAND_H



class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;

};

class CMD_Quit : public Command {
public:
    CMD_Quit(void *t_window) : _Window(t_window) {}

    void execute() override;

private:
    void* _Window;
};

class CMD_MoveCamera : public Command {
public:
    CMD_MoveCamera(void *t_game, int t_direction) : _Direction(t_direction), _Game(t_game) {}

    void execute() override;

private:
    int _Direction;
    void* _Game;
};

class  CMD_ZoomMap : public Command {
public:
    CMD_ZoomMap(void *t_game, double *t_yoffset) : _Game(t_game), _ScrollOffset(t_yoffset) {}

    void execute() override;

private:
    void* _Game;
    double* _ScrollOffset;
};

class CMD_BoxSelect : public Command {
public:
    CMD_BoxSelect(void *t_game, double *t_startx, double *t_starty, double *t_endx, double *t_endy)
    : _Game(t_game) ,_StartX(t_startx), _StartY(t_starty), _EndX(t_endx), _EndY(t_endy) {}

    void execute() override;

private:
    void* _Game;
    double* _StartX;
    double* _StartY;
    double* _EndX;
    double* _EndY;
};

class CMD_MoveTestUnit : public Command {
public:
    CMD_MoveTestUnit(void *t_game, double *t_xpos, double *t_ypos) : _Game(t_game), _Xpos(t_xpos), _Ypos(t_ypos) {}

    void execute() override;

private:
    void* _Game;
    double* _Xpos;
    double* _Ypos;
};

#endif //OPENBROODCRAFT_COMMAND_H
