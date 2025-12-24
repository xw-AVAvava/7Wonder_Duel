#ifndef FORWARD_H
#define FORWARD_H

// 前向声明所有主要类,避免循环依赖

class Game;
class GameBoard;
class MilitaryTrack;
class CardStructure;
class CardSlot;

class Player;
class HumanPlayer;
class AIPlayer;

class PlayerStrategy;
class HumanStrategy;
class AIStrategy;
class RandomAI;
class GreedyAI;

class Card;
class RawMaterialCard;
class ManufacturedGoodCard;
class CivilianCard;
class ScientificCard;
class MilitaryCard;
class CommercialCard;
class GuildCard;
class WonderCard;

class CardFactory;
class Cost;
class ResourceManager;
class ProgressToken;
class MilitaryToken;
class GameState;
class Action;
class VictoryCondition;
class ConsoleDisplay;
class InputHandler;

#endif // FORWARD_H
