#include <bits/stdc++.h>

using namespace std;


//print vector
void print_ans(vector<vector<int>>&ans,int source_num,int destination_num)
{
    for(int i=0;i<source_num;i++)
    {
        for(int j=0;j<destination_num;j++)
        {
            cout<<ans[i][j]<<" ";
        }
        cout<<"\n";
    }
}



//check if the problem is balanced or unbalanced
int check_if_unbalanced(vector<int>source,int source_num,vector<int>destination,int destination_num)
{
    int supply=0;
    for(int i=0;i<source_num;i++)
    supply+=source[i];

    int demand=0;
    for(int i=0;i<destination_num;i++)
    demand+=destination[i];

    return supply-demand;
}



//north-west corner rule
vector<vector<int>> north_west_rule(vector<int>source,vector<int>destination)
{
    vector<vector<int>> ans( source.size() , vector<int> (destination.size(), 0));
    for(int i=0;i<source.size();i++)
    {
        for(int j=0;j<destination.size() && source[i]!=0;j++)
        {
            ans[i][j]=min(source[i],destination[j]);
            source[i]-=ans[i][j];
            destination[j]-=ans[i][j];
        }
    }
    return ans;
}


//minimum cost rule
vector<vector<int>> minimum_cost_rule(vector<int>source,vector<int>destination,vector<vector<int>>cost)
{
    //create vector ans with default value 0
    vector<vector<int>> ans( source.size() , vector<int> (destination.size(), 0));
    
    for(int i=0;i<destination.size();i++)
    {
        //create vector with cost of ith destination
        vector<int>dest_cost;
        for(int j=0;j<source.size();j++)
            dest_cost.push_back(cost[j][i]);
        
        //let minimum cost be from first source
        int k=0;
        int minimum_cost;
        int loc;

        while(destination[i]!=0)
        {
            for(int j=0;j<source.size();j++)
            {
                if(dest_cost[j]!=-1)
                {
                    minimum_cost=dest_cost[j];
                    loc=j;
                    break;
                }
            }

            for(int j=0;j<source.size();j++)
            {   
                if(minimum_cost>=dest_cost[j] )
                {
                    if(dest_cost[j]!=-1)
                    {
                        minimum_cost=dest_cost[j];
                        loc=j;
                    }
                }
            }

            dest_cost[loc]=-1;

            ans[loc][i]=min(source[loc],destination[i]);
            source[loc]-=ans[loc][i];
            destination[i]-=ans[loc][i];
        }
    }

    return ans;

}


//c-(u+j)
vector<vector<int>>c_u_v(vector<int>source,vector<int>destination,vector<vector<int>>cost,vector<vector<int>>ans)
{
    vector<int>u(source.size(),10000);
    vector<int>v(destination.size(),10000);
    vector<vector<int>>p(source.size(),vector<int>(destination.size(),10000));

    bool flag1=true;
    bool flag=true;

    // vector<int>final_check_u;
    // vector<int>final_check_v;


    while(flag)
    {

        // vector<int>temp_check_u;
        // vector<int>temp_check_v;

        for(int i=0;i<source.size();i++)
        {
            for(int j=0;j<destination.size();j++)
            {
                if(ans[i][j]!=0)
                {
                    if(flag1)
                    {
                        flag1=false;
                        u[i]=0;
                        v[j]=cost[i][j]-u[i];
                    } 

                    else if(u[i]!=10000 && v[j]==10000)
                    {
                        v[j]=cost[i][j]-u[i];
                    }

                    else if (u[i]==10000 && v[j]!=10000)
                    {
                        u[i]=cost[i][j]-v[j];
                    }
                }
            }
        }
        
        int count_u=0,count_v=0;

        for(int i=0;i<source.size();i++)
        {
            if(u[i]!=10000)
            count_u+=1;
            // else
            // temp_check_u.push_back(i);
        }

        for(int j=0;j<destination.size();j++)
        {
            if(v[j]!=10000)
            count_v+=1;
            // else
            // temp_check_v.push_back(j);
        }

        if(count_u==source.size() && count_v==destination.size())
        flag=false;

        // if(final_check_u.size()==0 && final_check_v.size()==0)
        // {
        //     for(int i=0;i<temp_check_u.size();i++)
        //     final_check_u.push_back(temp_check_u[i]);
         
        //     for(int i=0;i<temp_check_u.size();i++)
        //     final_check_v.push_back(temp_check_v[i]);
        // }

        // else
        // {
        //     if(final_check_u==temp_check_u)
        //     {
        //         // cout<<"here";
        //         // if(final_check_u[0]<source.size())
                
        //         u[final_check_u[0]]=0;
        

        //         final_check_u.clear();
        //         final_check_v.clear();
        //     }
        // }

    }


    cout<<"\nu:\n";
    for(int i=0;i<source.size();i++)
    {
        cout<<u[i]<<" ";
    }
    cout<<"\nv:\n";
    for(int j=0;j<destination.size();j++)
    {
        cout<<v[j]<<" ";
    }
    cout<<"\n";
    for(int i=0;i<source.size();i++)
    {
        for(int j=0;j<destination.size();j++)
        {
            if(ans[i][j]==0)
            {
                p[i][j]=cost[i][j]-(u[i]+v[j]);
            }
        }
    }

    cout<<"\nP=cost[i][j]-(source[i]+destination[j]):\n";
    for(int i=0;i<source.size();i++)
    {
        for(int j=0;j<destination.size();j++)
        {
            if(p[i][j]==10000)
            cout<<"N ";
            else
            cout<<p[i][j]<<" ";

        }
        cout<<"\n";
    }

    return p;
}



//check optimal
//if no bool=false
//if yes: bool=true and loc of the cell which we should make it to basic cell 
pair<bool,pair<int,int>>check_optimal(vector<int>source,vector<int>destination,vector<vector<int>>cost_diff)
{
    
    int lowest=10000;
    bool flag=true;
    int lowest_row,lowest_column;
    for(int i=0;i<source.size();i++)
    {
        for(int j=0;j<destination.size();j++)
        {
            
            if(lowest>cost_diff[i][j])
            {
                lowest=cost_diff[i][j];
                lowest_row=i;
                lowest_column=j;
            }
        }
    }

    if(lowest>=0)
    {
        return make_pair(true,make_pair(0,0));
    }

    else
    {
        return make_pair(false,make_pair(lowest_row,lowest_column));
        cout<<"neighbouring bfs at: "<<lowest_row<<" "<<lowest_column;
    }
    
}




vector<vector<int>>get_cycle(vector<vector<int>>ans,int source_size,int destination_size,int n_bfs_row,int n_bfs_column,pair<int,int>&minus_sign_coordinate)
{
    
    vector<vector<int>>cycle(source_size,vector<int>(destination_size,0));

    for(int i=0;i<source_size;i++)
    {
        for(int j=0;j<destination_size;j++)
        {
            if(ans[i][j]!=0)
            cycle[i][j]=1;
        }
    }

    print_ans(cycle,source_size,destination_size);
    cout<<"\n";

    //to check whether the row/column has only one basic cell
    int flag=0;

    for(int k=1;k<=source_size-1;k++)
    {   
        //check single basic cell column-wise
        for(int j=0;j<destination_size;j++)
        {
            for(int i=0;i<source_size;i++)
            {
                if(cycle[i][j]==1)
                flag+=1;
            }

            if(flag==1 && j!=n_bfs_column)
            {
                for(int i=0;i<source_size;i++)
                {
                    if(cycle[i][j]==1)
                    {
                        cycle[i][j]=0;
                        break;
                    }
                }
            }

            flag=0;
        }

        //check single basic cell row-size
        flag=0;
        for(int i=0;i<source_size;i++)
        {
            for(int j=0;j<destination_size;j++)
            {
                if(cycle[i][j]==1)
                flag+=1;
            }

            if(flag==1 && i!=n_bfs_row)
            {
                for(int j=0;j<destination_size;j++)
                {
                    if(cycle[i][j]==1)
                    {
                        cycle[i][j]=0;
                        break;
                    }
                }
            }
            flag=0;
        }
    }
    cycle[n_bfs_row][n_bfs_column]=1;

    print_ans(cycle,source_size,destination_size);

    
    //find sign
    vector<vector<int>>sign(source_size,vector<int>(destination_size,0));
    sign[n_bfs_row][n_bfs_column]=1;

    int start_row=0,start_column=n_bfs_column;
    int x=-1;

    int flag_count=0;

    
    while(1==1)
    {
        for(int i=0;i<source_size;i++)
        {
            if(i==n_bfs_row && start_column==n_bfs_column)
            flag_count+=1;

            if(cycle[i][start_column]==1 && sign[i][start_column]==0)
            {
                sign[i][start_column]=x;
                x*=-1;
                start_row=i;
                break;
            }
        }


        for(int j=0;j<destination_size;j++)
        {
            if(start_row==n_bfs_row && j==n_bfs_column)
            flag_count+=1;

            if(cycle[start_row][j]==1 && sign[start_row][j]==0)
            {
                sign[start_row][j]=x;
                x*=-1;
                start_column=j;
                break;
            }
        }

        if(flag_count==2)
        break;
    }

    cout<<"\n";

    
    int min_check=10000;
    for(int i=0;i<source_size;i++)
    {
        for(int j=0;j<destination_size;j++)
        {
            if((sign[i][j]==-1) && (min_check==10000 || min_check>ans[i][j]))
            {
                min_check=ans[i][j];
                minus_sign_coordinate.first=i;
                minus_sign_coordinate.second=j;
            }

        }
    }

    return sign;

}




int main()
{
    cout<<"TRANSPORTATION PROBLEM\n";
    
    //get number of sources and destination
    int source_num,destination_num;
    cout<<"Enter Number of Sources:\n";
    cin>>source_num;
    cout<<"Enter Number of Destination:\n";
    cin>>destination_num;

    //create array sources and destination
    vector<int>source;
    vector<int>destination;

    //store quantity of each source(warehouse) in sources array
    int temp;
    cout<<"enter the quantity of each source:\n";
    for(int i=0;i<source_num;i++)
    {
        cin>>temp;
        source.push_back(temp);

    }

    //store quantity required in each destination in destination array
    cout<<"enter the quantity required in each destination:\n";
    for(int i=0;i<destination_num;i++)
    {
        cin>>temp;
        destination.push_back(temp);
    }

    //create cost array
    vector<vector<int>> cost;    
    //store cost in cost array
    cout<<"enter cost\n";
    for(int i=0;i<source.size();i++)
    {   
        vector<int>temp_vector;
        for(int j=0;j<destination.size();j++)
        {
            cin>>temp;
            temp_vector.push_back(temp);
        }
        cost.push_back(temp_vector);
    }

    
    int check=check_if_unbalanced(source,source_num,destination,destination_num);
    if(check==0)
    {
        cout<<"\nThe problem is balanced";
    }
    else if (check>0)
    {
        cout<<"\ncreating a dummy destinaition\n";
        
        //creating dummy destination with quantity source-demand       
        destination_num+=1;
        destination.push_back(check);

        for(int i=0;i<source_num;i++)
            cost[i].push_back(0);

    }
    else
    {
        cout<<"\nCreating a dummy source\n";
        
        //creating dummy source with quantity -1*(source-demand)       
        source_num+=1;
        source.push_back(check*(-1));
        
        vector<int>temp;
        for(int i=0;i<source_num;i++)
            temp.push_back(0);

        cost.push_back(temp);
    }
    
    


    //creating vector ans source_num rows and destination_num columns
    vector<vector<int>> ans( source_num , vector<int> (destination_num, 0));

    cout<<"\nSelect method to create a basic feasible solution\n";
    cout<<"1-North-West Corner Rule\n";
    cout<<"2-Minimum Cost Rule\n";

    int choice;
    cin>>choice;

    switch (choice)
    {
        case 1:
            ans=north_west_rule(source,destination);
            cout<<"\n***************************************";
            cout<<"\nBasic Feasible Solution from North-West Corner Rule:\n\n";
            break;
        case 2:
            ans=minimum_cost_rule(source,destination,cost);
            cout<<"\n***************************************";
            cout<<"\nBasic Feasible Solution from Minimum Cost Rule:\n\n";
            break;
        default:
            cout<<"Wrong Choice";
            exit(0);
            break;
    }


    print_ans(ans,source.size(),destination.size());

    int count=0;
    
    while(1==1)
    {
        //u-v method
        vector<int>u(source.size(),10000);
        vector<int>v(destination.size(),10000);
        vector<vector<int>>cost_diff(source.size(),vector<int>(destination.size(),10000));


        cost_diff=c_u_v(source,destination,cost,ans);

        //check optimal or not
        pair<bool,pair<int,int>>check_optimality=check_optimal(source,destination,cost_diff);
        //if optimal
        if(check_optimality.first==true)
        {   
            cout<<"**************END*************\n";
            cout<<"Solution reached optimality";

            cout<<"\n\n";
            print_ans(ans,source.size(),destination.size());
            

            cout<<"\n\nPrice:";

            int price=0;
            for(int i=0;i<source.size();i++)
            {
                for(int j=0;j<destination.size();j++)
                {
                    price+=(ans[i][j]*cost[i][j]);
                }
            }

            cout<<price;

            cout<<"\n**************END*************";
    
            break;

        }
        else
        {
            
            // cout<<check_optimality.second.first<<" "<<check_optimality.second.second;
            count+=1;
            cout<<"\n***************************************";
            cout<<"\nStep "<<count<<" :\n";


            int n_bfs_row=check_optimality.second.first;
            int n_bfs_column=check_optimality.second.second;

            cout<<"neighbour bfs cell at: "<<n_bfs_row<<" "<<n_bfs_column<<"\n";        
            
            pair<int,int>min_minus_sign_coordinates;
            vector<vector<int>>cycle=get_cycle(ans,source.size(),destination.size(),n_bfs_row,n_bfs_column,min_minus_sign_coordinates);
            
            cout<<"\nCycle with sign:\n";
            print_ans(cycle,source.size(),destination.size());
            cout<<"\n";
            int num=ans[min_minus_sign_coordinates.first][min_minus_sign_coordinates.second];

            for(int i=0;i<source.size();i++)
            {
                for(int j=0;j<destination.size();j++)
                {
                    if(cycle[i][j]==1||cycle[i][j]==-1)
                    ans[i][j]+=(num*cycle[i][j]);
                }
            }

            print_ans(ans,source.size(),destination.size());

            cout<<"\n\nPrice:";

            int price=0;
            for(int i=0;i<source.size();i++)
            {
                for(int j=0;j<destination.size();j++)
                {
                    price+=(ans[i][j]*cost[i][j]);
                }
            }
            cout<<price;

            // cout<<"\n***************************************\n";

        }

        if(count==100)
        break;


    }

}   