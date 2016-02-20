#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include "card.h"

class Table
{
private:
    /**
     * @brief FourOfAKinds A vector of vectors of size four. Each internal vector contains four of one rank of card that has been
     * placed by one Player or another.
     */
    std::vector<std::vector<Card> > FourOfAKinds;
    std::vector<std::vector<Card> >::iterator iter;
public:
    void add(std::vector<Card>);

    /**
     * @brief get Returns the vector of Cards that corresponds to a given rank. If no cards of that rank are found, this method returns
     * an empty vector of Cards.
     */
    std::vector<Card> get(int rank);

    /**
     * @brief Table Initializes FourOfAKinds
     */
    Table();
    ~Table();
};

#endif // TABLE_H
