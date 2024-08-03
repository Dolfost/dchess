#include "../include/testutils.hpp"

#include <iostream>

using namespace std;

Chessboard::PieceTypesRetT getPiece(Chessboard::PieceTypesArgT types) {
	char piece; 
	type_index type = typeid(nullptr);

	do {
		cout << "Enter Piece for exchange: ";
		cin >> piece;
		piece = tolower(piece);
		cout << endl << piece << endl;
		switch (piece) {
			case 'p':
				type = typeid(Pawn);
				break;
			case 'k':
				type = typeid(Knight);
				break;
			case 'b':
				type = typeid(Bishop);
				break;
			case 'r':
				type = typeid(Rook);
				break;
			case 'q':
				type = typeid(Queen);
				break;
		}
	} while(type == typeid(nullptr));

	return type;
}

void move(Chessboard& cb,
								 Piece::Position from,
								 Piece::Position to,
								 bool rethrow) {
		try {
			cb.makeTurn(from, to);
		} catch (logic_error& e) {
			if (rethrow)
				throw e;
			cout << e.what() << endl;
		}
}

void play(Chessboard& cb, 
					Chessboard::TurnsT t, 
					bool rethrow) {
	cb.setPieceGetter(getPiece);
	int no = 1;
	cout << "Board:\n" << cb;
	for (auto& t : t) {
		cout << "\n" << "Turn №" << no++ << ": " 
			<< t.first << "->" << t.second << endl;
		try {
			move(cb, t.first, t.second, rethrow);
		} catch (std::exception& ex) {
			throw ex;
		}
		cout << cb << flush;
	}
}

void interactive_play(Chessboard& cb, bool rethrow) {
	string mv;
	Piece::Position from, to;
	int no = 0;
	cout << "Board:\n" << cb;
	while (cout << "Enter move: " and cin >> mv) {
		if (mv == "q")
			return;
		if (mv == "b") {
			cout << cb << flush;
			continue;
		}
		try {
			from = Piece::Position(mv.substr(0, 2));
			to = Piece::Position(mv.substr(2, 2));
		} catch (std::exception& ex) {
			if (rethrow)
				throw ex;
			cerr << "Error: " << ex.what() << endl;
			continue;
		}
		cout << "Turn №" << ++no << ": " 
			<< from << "->" << to << endl;
		move(cb, from, to, rethrow);
		cout << cb << flush;
	}
	cin.clear();
}