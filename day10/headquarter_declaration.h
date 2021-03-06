#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "WarcraftClassDeclaration.h"

class Headquarter
{
  private:
	typedef tuple<int, Samurai *, int> quetype;
	string name;
	vector<function<Samurai *(Headquarter *)>> Order;
	vector<function<Weapon *(Samurai *)>> Weapons;
	vector<int> ExistNumber;
	int HealthPoint, OnWitch = 0, Count = 0;
	int posi, dire, outputlevel;
	vector<quetype> que;

  public:
	Headquarter(const string &_name, int _HP,
				const vector<function<Samurai *(Headquarter *)>> &_Order,
				const vector<function<Weapon *(Samurai *)>> &_Weapons);
	Headquarter(const Headquarter &);
	tuple<Samurai *, string> Build_SA();
	unsigned int getOrderSize();
	unsigned int getWeaponsSize() { return Weapons.size(); }
	int getCount() const { return Count; }
	int generateNextSamurai(int);
	void changeCount(int x) { Count = x; }
	int getHP() const { return HealthPoint; }
	void changeHP(int x) { HealthPoint = x; }
	Weapon *getweapon(int, Samurai *) const;
	int get_pos() const { return posi; }
	void set_pos(int x) { posi = x; }
	int get_direct() const { return dire; }
	void set_direct(int x) { dire = x; }
	int get_outputlevel() const { return outputlevel; }
	void set_outputlevel(int x) { outputlevel = x; }
	string getname() const { return name; }
	void receiveHP(int x = 0) { HealthPoint += x; }
	void askforHP(quetype x) { que.push_back(x); }
	void clearque();
	~Headquarter() = default;
};

class TIME
{
	int minutes;

  public:
	TIME() = default;
	TIME(int x) : minutes(x){};
	void inc(int a) { minutes += a; }
	void Print()
	{
		printf("%03d:%02d", minutes / 60, minutes % 60);
	}
	string sPrint()
	{
		char tmp[10];
		sprintf(tmp, "%03d:%02d", minutes / 60, minutes % 60);
		return tmp;
	}
	bool operator<(const TIME t) { return minutes < t.minutes; }
	bool operator>(const TIME t) { return minutes > t.minutes; }
};

class OrderedOutput
{
	vector<pair<int, string>> data;

  public:
	void push(int t, string x) { data.push_back(make_pair(t, x)); }
	void flush()
	{
		sort(data.begin(), data.end(), [](const pair<int, string> &a, const pair<int, string> &b) { return a.first < b.first; });
		
		for (auto &x : data)
		{
			cout << x.second;
		}
		data.clear();
	}
	~OrderedOutput()
	{
		flush();
	}
};

class City
{
	typedef set<Samurai *> SamuraiSet;
	SamuraiSet samurais;
	int pos, HP = 0;
	Headquarter *possessed = NULL, *_definedfirst = NULL;
	Headquarter *last_win = NULL;

  public:
	City() = default;
	void insert(Samurai *x) { samurais.insert(x); }
	void erase(Samurai *const &x) { samurais.erase(x); }
	SamuraiSet::const_iterator begin() const { return samurais.cbegin(); }
	SamuraiSet::const_iterator end() const { return samurais.cend(); }
	SamuraiSet::const_reverse_iterator rbegin() const { return samurais.crbegin(); }
	SamuraiSet::const_reverse_iterator rend() const { return samurais.crend(); }
	void set_pos(int x) { pos = x; }
	int get_pos() const { return pos; }
	unsigned int size() const { return samurais.size(); }
	void generateHP() { HP += 10; }
	void win(Headquarter *);
	Headquarter *deffirst() const { return _definedfirst; }
	void setdeffirst(Headquarter *x) { _definedfirst = x; }
	Headquarter *conquer() const { return possessed; }
	string fightresult(Headquarter *a)
	{
		if (a != NULL && last_win == a && possessed != a){
			possessed = last_win;
			return a->getname() + " flag raised in city " + to_string(get_pos());
		}
		last_win = a;
		return "";
	}
	int lostHP();
};

class BattleField
{
	TIME T;
	int Size;
	Headquarter HeadA, HeadB;
	City *city;

  public:
	BattleField(int n, Headquarter a, Headquarter b);
	void Run(TIME);
	void BuildTurn();
	int MoveTurn();
	void BattleTurn();
	vector<string> Fight(Samurai *, Samurai *);
	bool FightFirst(Samurai *, Samurai *);
	~BattleField();
};