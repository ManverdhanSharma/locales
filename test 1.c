void setup(void)

{

    setlocale(LC_ALL, "");

    initscr(); cbreak(); noecho();

    nonl();

    intrflush(stdscr, FALSE);

    keypad(stdscr, TRUE);

    timeout(0);

    curs_set(0);

    getmaxyx(stdscr, height, width);

    width = (width + 1) / 2;

    snk = new_node(width / 2, 0, NULL);

    len = 1;

    dir = DOWN;

    do {

        food_x = rand() % width;

        food_y = rand() % height;

    } while (snk->x == food_x && snk->y == food_y);

    gameover = false;

    srand(time(0));

}  