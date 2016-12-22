#include <time.h>
#include <iostream>
class field;
class place;
class sell;
class pred;
class sell_data;
class sell_brain;
class predator_data;
class pred_brain;

void sell_ask_for_params(sell* asker);

void sell_brain_processing(sell * me);

void add_brain_to_sell(sell* me);

void pred_ask_for_params(pred* asker);

void pred_brain_processing(pred * me);

void add_brain_to_pred(pred* me);