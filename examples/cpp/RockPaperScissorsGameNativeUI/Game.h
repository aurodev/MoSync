/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/**
 * @file Game.h
 *
 * This file contains the game logic for the game.
 *
 * Game logic:
 * The game is started by clicking the Start button, and that enables the
 * user to select a weapon from the 3 available ones.
 * The opponent's weapon is chosen randomly, and it is shown only after
 * the user has picked his weapon.
 * The game result is displayed using two strings: who won the game, and why.
 * The score info at the bottom is updated after each game is finished.
 * Game can be restarted by pressing the Start button again.
 *
 * @author Emma Tresanszki
 */

#ifndef GAME_H_
#define GAME_H_
#include <MAUtil/String.h>

namespace RockPaperScissors
{

/**
 * Strings for the game result.
 */
const MAUtil::String ROCK_vs_SCISSORS = "ROCK breaks SCISSORS";
const MAUtil::String SCISSORS_vs_PAPER = "SCISSORS cut PAPER" ;
const MAUtil::String PAPER_vs_ROCK = "PAPER captures ROCK";
const MAUtil::String YOU_WIN = "YOU WIN!";
const MAUtil::String YOU_LOSE = "YOU LOSE";

/**
 * Available weapons.
 */
enum eWeapons
{
	ROCK = 1,
	PAPER,
	SCISSORS
};

/**
 * Possible results.
 */
enum eResult
{
	TIE,
	WIN,
	LOSS
};

/**
 * The Game Engine class.
 * Computes the game based on a user selected weapon,
 * and a random rival weapon.
 * It provides total number of wins, looses and ties,
 * and also the explanation for each result.
 */
class Game
{

public:
	/**
	 * Constructor for the Game class.
	 * Here instance variables are initialized.
	 */
	Game();

	/*
	 * Empty destructor.
	 * We don't need to do any special cleanup.
	 */
	virtual ~Game();

	/**
	 * Set the currently used weapon.
	 * @param myWeapon The weapon to be used.
	 */
	void setMyWeapon(const eWeapons myWeapon);

	/**
	 * Set a random weapon for opponent.
	 */
	void setRandomOpponentWeapon();

	/**
	 * Get the opponent's weapon.
	 * @return The constant describing the weapon.
	 */
	eWeapons getOpponentWeapon();

	/**
	 * Get the total number of rounds played.
	 * @return Number of rounds.
	 */
	int getTotalRounds();

	/**
	 * Get the total number of losses for the player.
	 * @return Number of losses.
	 */
	int getLosesNr();

	/**
	 * Get the total number of wins for the player.
	 * @return Number of wins.
	 */
	int getWins();

	/**
	 * Get the total number of ties.
	 * @return Number of ties.
	 */
	int getTies();

	/**
	 * Get the explanation for the outcome of
	 *  the last round in the game.
	 * @return String with the explanation, for example:
	 *  "ROCK breaks SCISSORS"
	 */
	const MAUtil::String& getExplanation();

	/**
	 * Get the winner of the last round in the game.
	 * @return String with winner, for example: "YOU WIN!"
	 */
	const MAUtil::String& getWinState();

	/**
	 * Compute the outcome of the current round, based
	 * on the players weapon, and the opponent's weapon.
	 */
	void computeGameResult();

private:
	/** My weapon type. */
	eWeapons mMyWeapon;

	/** The opponents's weapon type. */
	eWeapons mOpponentWeapon;

	/** The current result from the last round. */
	eResult mResult;

	/** Total number of wins */
	int mWins;

	/** Total number of losses. */
	int mLoses;

	/** Total number of ties. */
	int mTies;

	/** Total number of played rounds. */
	int mTotalRounds;

	/** Description of who has win the last round. */
	MAUtil::String mWinState;

	/** Explanation of the win state. */
	MAUtil::String mExplanation;
};

} // namespace RockPaperScissors

#endif // GAME_H_
