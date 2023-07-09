#include<iostream>
#include<climits>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<math.h>
#include<iomanip>
#include<string>
using namespace std;

template <typename X>
class graph{ 

    private:

		//storing inter-connected cities in an oredered map with there name and distance or weight in pair
        map<X, list<pair<X,int> > > m;

		//avg speed of diff transports

		double bus_speed = 50;
		double train_speed = 80;
		double car_speed = 70;
		double plane_speed = 500;

		//counter
		int i = 1;

		// Stroing destination and sources
		X des;
		X src;

		// Total distance from source to destination.
        double distance = 0;

		//total time taken by different sources.
        double bus_time = 0;
        double car_time = 0;
        double train_time = 0;
        double plane_time = 0;

		//time calculating tool
		double bus_before_dec = 0;
		double bus_after_dec = 0;
		double train_before_dec = 0;
		double train_after_dec = 0;
		double car_before_dec = 0;
		double car_after_dec = 0;
		double plane_before_dec = 0;
		double plane_after_dec = 0;

		//Cost calculating tools
		double bus_cost = 0;
		double car_cost = 0;
		double train_cost = 0;
		double plane_cost = 0;

		//Base fare of different Transports and ther perkm fair
		//Base fair is just for 50 km for bus, car, plane and train.
		int bus_base_fare = 200;
		int bus_per10km = 70;

		int  car_base_fare = 500;
		int car_per10km = 80;

		int train_base_fare = 400;
		int train_per10km = 50;


		int plane_base_fare = 1000;
		int plane_per10km = 150;


		string bus = "BUS";
		string train = "TRAIN";
		string car = "CAR";
		string plane = "AEROPLANE";

		int x = 0;

		string name_arr[7];
		string lname_arr[7];
		int age_arr[7];

		double total_cost = 0;
		double cost =0;

    public:

		// Adding nodes with one another and making them bi-directional
		//it is working like a list. multilinked list

        void addEdge(X u,X v,int dist,bool bidir=true){

        	m[u].push_back(make_pair(v,dist));

        	if(bidir){

            	m[v].push_back(make_pair(u,dist));

        	}
        
    	}

		// this function is to print the all cities. in an ordered way or alphabatical order.
        void print(){
			

            for(auto j:m){
            
                cout<<i<<". "<<j.first;

				if(i%2 == 0){

					cout<<endl;

				}
				else{

					int spacesize = 50;
					string str = j.first;
					int size = str.length();
					spacesize = spacesize-size;
					for(int i=0;i<spacesize;i++){

						cout<<" ";

					}
				}
                i++;
            }
        }

		//dijkstra's algorithm or single source shortest path algorithm that can be used to calculate the shortest path between the node

        void SSSP(){

		    map<X,int> dist;
		    map<X,X> parent_map;
		    set<pair<int,X> >s;



		    for(auto node:m){

			    dist[node.first] = INT_MAX;

		    }

		    dist[src] = 0;
		    parent_map[src] = src;
		    s.insert(make_pair(0,src));

		    while(!s.empty()){

			    auto p = (*s.begin());
			    X parent = p.second;
			    int parent_dist = p.first;
			    s.erase(s.begin());

			    for(auto children:m[parent]){

				    if(dist[children.first]>dist[parent]+children.second){

					    auto f = s.find(make_pair(dist[children.first],children.first));

					    if(f!=s.end()){

						    s.erase(f);

					    }

					    dist[children.first] =dist[parent]+children.second;
					    parent_map[children.first] = parent;
					    s.insert(make_pair(dist[children.first],children.first));

				    }
			    }
		    }
            
            for(auto d:dist){
                
                if(des == d.first){

                    distance = d.second;

                }
            }

		    X temp = des;

		    while(temp!=src){

			    cout<<temp<<"<--";
			    temp=parent_map[temp];
                

		    }
		    cout<<src<<endl;
            cout<<"Total Distance :- "<<distance<<endl;

	}

	void addingedges(){

		  addEdge("Amritsar","Delhi",500);
    	addEdge("Amritsar","Jaipur",450);
    	addEdge("Jaipur","Delhi",250);
    	addEdge("Jaipur","Mumbai",800);
    	addEdge("Bhopal","Agra",200);
    	addEdge("Mumbai","Bhopal",700);
    	addEdge("Agra","Delhi",180);
    	addEdge("Delhi","Siacin",700);

	}

	void checksource(int source){

		if(source>=i){

			cout<<"Invalid Entry"<<endl;

		}
		else{

			int checkr = 1;
			for(auto j:m){

				if(checkr == source){

					src = j.first;
                    cout<<src;
                    break;

				}
                checkr++;
			}
		}
	}

	void checkdest(int destin){

		if(destin>=i){

			cout<<"Invalid Entry"<<endl;
			
		}
		else{

			int checkr = 1;
			for(auto j:m){

				if(checkr == destin){

					des = j.first;
                    cout<<des;
                    break;

				}
                checkr++;
			}
		}
	}

    void timefunction(){

		//Bus 
		bus_time = distance/bus_speed;
		
		bus_after_dec = modf(bus_time,&bus_before_dec);
		bus_after_dec = (bus_after_dec*6)/10;
		bus_time = bus_after_dec + bus_before_dec;

		//Car
		car_time = distance/car_speed;
		
		car_after_dec = modf(car_time,&car_before_dec);
		car_after_dec = (car_after_dec*6)/10;
		car_time = car_after_dec + car_before_dec;

		//Train
		train_time = distance/train_speed;
		
		train_after_dec = modf(train_time,&train_before_dec);
		train_after_dec = (train_after_dec*6)/10;
		train_time = train_after_dec + train_before_dec;

		//Plane
		plane_time = distance/plane_speed;
		
		plane_after_dec = modf(plane_time,&plane_before_dec);
		plane_after_dec = (plane_after_dec*6)/10;
		plane_time = plane_after_dec + plane_before_dec;

    }
	
	int busfunction(){

		int x = distance;
		int total_cost = bus_base_fare;
		x -= 50;

		int j = x/10;

		total_cost += j*bus_per10km;
		return total_cost;
		
	}

	int trainfunction(){

		int x = distance;
		int total_cost = train_base_fare;
		x -= 50;

		int j = x/10;

		total_cost += j*train_per10km;
		return total_cost;
		
	}

	int carfunction(){

		int x = distance;
		int total_cost = car_base_fare;
		x -= 50;

		int j = x/10;

		total_cost += j*car_per10km;
		return total_cost;
		
	}

	int planefunction(){

		int x = distance;
		int total_cost = plane_base_fare;
		x -= 50;

		int j = x/10;

		total_cost += j*plane_per10km;
		return total_cost;
		
	}

	//Function to calculate the Travel Cost
	void Travel_cost(){

		bus_cost = busfunction();

		car_cost = carfunction();

		train_cost = trainfunction();

		plane_cost = planefunction();

	}

	void space(int i){

		for(int i=0;i<30-i;i++){

			cout<<" ";

		}


	}

	void space(string naam){

		for(int i=0;i<30-naam.length();i++){

			cout<<" ";

		}

	}
	
	void print_all(){

		for(int i=1;i<=100;i++){

			cout<<"*";

		}
		cout<<endl;

		cout<<"Transport Modes";
		space("Transport Modes");
		cout<<"TIME";
		space("aaa");
		cout<<"PRICE"<<endl;

		cout<<bus;
		space(bus);
		cout<<fixed<<setprecision(2)<<bus_time;
		space("aaa");
		cout<<bus_cost<<endl;

		cout<<train;
		space(train);
		cout<<fixed<<setprecision(2)<<train_time;
		space("aaa");
		cout<<train_cost<<endl;
		

		cout<<car;
		space(car);
		cout<<fixed<<setprecision(2)<<car_time;
		space("aaa");
		cout<<car_cost<<endl;

		cout<<plane;
		space(plane);
		cout<<fixed<<setprecision(2)<<plane_time;
		space("aaa");
		cout<<plane_cost<<endl;
		
	}

	void printticket(int i){

		cout<<"Mode of Transport";
		space("");
		if(i == 1){

			cout<<"BUS"<<endl;
			cost = bus_cost;

		}
		else if(i == 2){

			cout<<"CAR"<<endl;
			cost = car_cost;

		}
		else if(i == 3){

			cout<<"TRAIN"<<endl;
			cost = train_cost;

		}
		else{

			cout<<"PLANE"<<endl;
			cost = plane_cost;

		}

		cout<<"Passenger Name";
		space("Passenger Name");
		cout<<"Age";
		space("");
		cout<<"Price"<<endl;


		for(int i=0;i<x;i++){

			cout<<name_arr[i];
			space(name_arr[i]);
			cout<<age_arr[i];
			space("aa");
			cout<<cost<<endl;

		}
		cout<<endl;
		cout<<"TOTAL COST :- ";
		space("");
		space("");
		total_cost = x*cost;
		cout<<total_cost<<endl;

	}

	void book(int i){

		space("");
		cout<<"Enter the No. of passangers"<<endl;
		cin>>x;

		for(int i=0;i<x;i++){

			cout<<" First Name of passanger :- ";
			cin>>name_arr[i];
			cout<<"Last Name of Passenger :- ";
			cin>>lname_arr[i];
			cout<<"Age :- ";
			cin>>age_arr[i];

		} 

		if(i == 1){

			printticket(1);

		}
		else if(i == 2){

			printticket(2);

		}
		else if(i == 3){

			printticket(3);

		}
		else{

			printticket(4);

		}
		
	}

};

int main(){

    graph<string> india;
	
	cout<<endl;
	india.space("");
	cout<<"Press 1. Start"<<endl;
	india.space("");
	cout<<"Press 2. To exit"<<endl;

	int n;
	cin>>n;
	india.addingedges();

	switch (n){
		case 1: {
	
			india.print();
			cout<<endl;
			cout<<"Enter starting point :-  ";
			int start;
			cin>>start;
			india.checksource(start);
			cout<<endl;

			cout<<"Enter destination point :- ";
			int destination;
			cin>>destination;
			india.checkdest(destination);
			cout<<endl;

			cout<<"Route map :- "<<endl;
    		india.SSSP();
			cout<<endl;
			india.space("");
			cout<<"Press 1. To check Cost and time for Different Modes of Transport"<<endl;
			india.space("");
			cout<<"Press 2. To EXIT"<<endl;
			int j = 0;
			cin>>j;
			switch (j){

				case 1:{
					india.timefunction();
					india.Travel_cost();
					india.print_all();
					
					india.space("");
					cout<<"Press 1. to Book Ticket"<<endl;
					india.space("");
					cout<<"Press 2. to Exit"<<endl;
					int f = 0;
					cin>>f;

					switch (f){
					case 1:{

						india.space("");
						cout<<"Press 1. to Book in BUS"<<endl;
						india.space("");
						cout<<"Press 2. to Book in  Car"<<endl;
						india.space("");
						cout<<"Press 3. to book in Train"<<endl;
						india.space("");
						cout<<"Press 4. to Book in Plane"<<endl;

						int m = 0;
						cin>>m;

						switch (m){
						case 1:{

							india.book(m);

							break;
						}
						case 2:{

							india.book(m);
							break;

						}
						case 3:{

							india.book(m);
							break;

						}
						case 4:{

							india.book(m);
							break;


						}
						default:{

							cout<<"Please press correct key"<<endl;
							break;

						}
							
					}

						break;

				}
						
					default:{

						break;
					}
						
				}

			}

		}
			break;
	}
	
		case 2:{

			return 0;

		}
	
		default:
			cout<<"Please Press Correct Key"<<endl;
			break;
	}

	return 0;

}