#include "tom.h"
#include "jerry.h"


Tom::Tom(int initialRow, int initialColumn, int d[20][20])
{

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            data[i][j] = d[i][j];
    row = initialRow;
    column = initialColumn;
    // Set Image
    QPixmap image("tomm.png");
    image = image.scaledToWidth(35);
    image = image.scaledToHeight(35);
    setPixmap(image);
    // Set Position
    setPos(50 + 35 * column, 50 + 35 * row);

//creating the adjacency Matrix

    //intialize all of the matrix with zeros
    for (int i = 0; i < COUNT; i++)
        {
        for (int j = 0; j < COUNT; j++)
                adjMatrix[i][j] = 0;
        }

    // the loop on the data in the board, for each number that is not negative, this will be the vertex.
    for (int i = 0; i <= 19; i++)
        {   for (int j = 0; j <= 19; j++)
               {
              int vertex = data[i][j];
    //make sure that the vertex is not inside the house because tom can't go there
    // then fill the adjacency matrix with 1's for the starting vertex( the one we are at)
    //and it's adjacent vertices(top, bottom,right,left)

             if (data[i][j] >=0 && !inHome(vertex))
 {

          if (data[i][j + 1] >= 0 && !inHome(data[i][j+1]))
          {
              adjMatrix[vertex][data[i][j+1]] = 1;
          }
            if(data[i-1][j]>=0 && !inHome(data[i - 1][j]))

            {
              adjMatrix[vertex][data[i-1][j]] = 1;

          }
            if(data[i][j-1]>=0 && !inHome(data[i][j - 1]))
          {
              adjMatrix[vertex][data[i][j-1]] = 1;
          }
            if(data[i+1][j]>=0 && !inHome(data[i + 1][j]))
          {

           adjMatrix[vertex][data[i+1][j]] = 1;
          }

          else
          {
              adjMatrix[vertex][data[i][j]] = 0;
          }
                 }
      }

    }

}

//returns tom to his original position and the bottom middle
void Tom::ReturnToOriginalPos()
{
    row = 18;
    column = 10;
    setPos(50 + 35 * column, 50 + 35 * row);
}

//Dijkstra gets all the paths from the starting Node to all other nodes
QVector<QVector<int> > Tom::Dijkstra(int Graph[COUNT][COUNT], int startVertex)
{
       int temp[COUNT][COUNT];
    for (int i = 0; i < COUNT; i++)
       {
           for (int j = 0; j < COUNT; j++)
           {
               if (Graph[i][j] == 0)
                   temp[i][j] = INFINITE;
               else
                   temp[i][j] = Graph[i][j];
           }
       }
       bool visited[COUNT];
       int previous[COUNT];
       float cost[COUNT];
       // 1st Row:
       for (int i = 0; i < COUNT; i++)
       {
           if (i == startVertex)
           {
               previous[i] = -1;
               cost[i] = 0;
               visited[i] = true;
           }
           else
           {
               previous[i] = startVertex;
               cost[i] = temp[startVertex][i];
               visited[i] = false;
           }
       }
       // All Rows:
       int count = 1;
       while (count < COUNT)
       {
           // Determine which vertex to visit.
           int minimum = INFINITE, visitedVertex;
           for (int i = 0; i < COUNT; i++)
           {
               if (visited[i] == false && cost[i] < minimum)
               {
                   minimum = cost[i];
                   visitedVertex = i;
               }
           }
           // Visit the vertex.
           visited[visitedVertex] = true;

           // Check whether there are shorter paths.
           for (int i = 0; i < COUNT; i++)
           {
               if (visited[i] == false)
               {
                   if ((cost[visitedVertex] + temp[visitedVertex][i]) < cost[i])
                   {
                       previous[i] = visitedVertex;
                       cost[i] = (cost[visitedVertex] + temp[visitedVertex][i]);
                   }
               }
           }
           count++;
       }
       // Extract the paths.
       QVector<QVector<int>> paths;
       paths.resize(COUNT);
       int j;
       for (int i = 0; i < COUNT; i++)
       {
           paths[i].push_back(i);
           if (i != startVertex)
           {
               j = i;
               do
               {
                   j = previous[j];
                   paths[i].insert(paths[i].begin(), j);
               } while (j != startVertex);
           }
       }

       return paths;

}

//this function makes tom move after jerry using the dijksra algorithm and the adjacency matrix
// it is responsible for the movement of Tom
void Tom::UpdateMotion()
{
    //If Tom needs to move
    if(moving){
    auto path = Dijkstra(adjMatrix, data[row][column]);

    //Checks the successor nodes and finds their values
    //If one of them matches the next in path then it moves accordingly.
     if(path[jerryVertex].size() > 1)
     {
         int nextNode = path[jerryVertex][1];
         int leftNode = data[row][column - 1];
         int rightNode = data[row][column + 1];
         int upNode = data[row - 1][column];
         int downNode = data[row + 1][column];

         if(nextNode  == leftNode)
             column--;
         else if (nextNode ==rightNode)
             column++;
         else if( nextNode == upNode)
             row--;
         else if(nextNode == downNode)
             row++;
     }
     setPos(50 + 35 * column, 50 + 35 * row);
    }

}

//used in the jerry class to know where jerry is at now
void Tom::SetJerryVertex(int v)
{
    jerryVertex = v;
}

// makes stop moving when the game is over
void Tom::stoppMoving()
{
    moving=false;
}

//Milestone1 Random Movement of Tom
void Tom::RandMotion()
{
    srand(time(NULL));
    int x = qrand()% 4 + 1;
    if (x==1 && data[row - 1][column] != -10)
        {
            int i;
            for (i=0; i < 9; i++)
                if (data[row - 1][column] == home[i])
                    break;
            if (i == 9)
                row--;
        }
        else if (x==2 && data[row + 1][column] != -10)
        {
            int i;
            for (i=0; i < 9; i++)
                if (data[row + 1][column] == home[i])
                    break;
            if (i == 9)
            row++;
        }
        else if (x==3 && data[row][column + 1] != -10)
        {
            int i;
            for (i=0; i < 9; i++)
                if (data[row][column + 1] == home[i])
                    break;
            if (i == 9)
            column++;
        }
        else if (x==4 && data[row][column - 1] != -10)// && data[row][column - 1] != home[i])
        {
            int i;
            for (i=0; i < 9; i++)
                if (data[row][column - 1] == home[i])
                    break;
            if (i == 9)
            column--;
        }
    setPos(50 + 35 * column, 50 + 35 * row);
}
