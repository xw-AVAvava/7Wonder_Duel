#include "../../include/cards/CardFactory.h"

template<typename T>
T* CardFactory::createCardWithCost(T* card, const std::vector<std::pair<ResourceType, int>>& resources, int coins) {
    Cost cost(coins);
    for (const auto& pair : resources) {
        cost.addResource(pair.first, pair.second);
    }
    card->setCost(cost);
    return card;
}

std::vector<Card*> CardFactory::createAgeIDeck() {
    std::vector<Card*> deck;
    
    // ========== 棕色卡牌(原材料) ==========
    deck.push_back(new RawMaterialCard("伐木场", 1, ResourceType::WOOD));
    
    auto* stonePit = new RawMaterialCard("石料坑", 1, ResourceType::STONE);
    stonePit->setCost(Cost(1));
    deck.push_back(stonePit);
    
    deck.push_back(new RawMaterialCard("黏土池", 1, ResourceType::CLAY));
    
    auto* clayPit = new RawMaterialCard("黏土坑", 1, ResourceType::CLAY);
    clayPit->setCost(Cost(1));
    deck.push_back(clayPit);
    
    auto* loggingCamp = new RawMaterialCard("林地", 1, ResourceType::WOOD);
    loggingCamp->setCost(Cost(1));
    deck.push_back(loggingCamp);
    
    deck.push_back(new RawMaterialCard("采石场", 1, ResourceType::STONE));
    
    // ========== 灰色卡牌(制成品) ==========
    deck.push_back(new ManufacturedGoodCard("玻璃工坊", 1, ResourceType::GLASS));
    deck.push_back(new ManufacturedGoodCard("压榨机", 1, ResourceType::PAPYRUS));
    
    // ========== 蓝色卡牌(平民建筑) ==========
    deck.push_back(new CivilianCard("祭坛", 1, 3));
    
    auto* theater = new CivilianCard("剧场", 1, 3);
    theater->setChainSymbol("THEATER");
    deck.push_back(theater);
    
    auto* baths = new CivilianCard("浴场", 1, 3);
    baths->setChainSymbol("BATHS");
    deck.push_back(createCardWithCost(baths, {{ResourceType::STONE, 1}}));
    
    auto* tribunal = new CivilianCard("法庭", 1, 5);
    deck.push_back(createCardWithCost(tribunal, {{ResourceType::WOOD, 2}}));
    
    // ========== 绿色卡牌(科学建筑) ==========
    auto* apothecary = new ScientificCard("药房", 1, ScientificSymbol::COMPASS, 1);
    apothecary->setChainSymbol("APOTHECARY");
    deck.push_back(createCardWithCost(apothecary, {{ResourceType::GLASS, 2}}));
    
    auto* workshop = new ScientificCard("工坊", 1, ScientificSymbol::WHEEL, 1);
    workshop->setChainSymbol("WORKSHOP");
    deck.push_back(createCardWithCost(workshop, {{ResourceType::PAPYRUS, 1}}));
    
    auto* scriptorium = new ScientificCard("经文馆", 1, ScientificSymbol::TABLET, 2);
    scriptorium->setChainSymbol("SCRIPTORIUM");
    deck.push_back(createCardWithCost(scriptorium, {{ResourceType::WOOD, 2}}));
    
    // ========== 黄色卡牌(商业建筑) ==========
    auto* tavern = new CommercialCard("酒馆", 1, CommercialEffect::COINS);
    tavern->setImmediateCoins(4);
    deck.push_back(tavern);
    
    auto* eastTradingPost = new CommercialCard("东方市场", 1, CommercialEffect::REDUCE_RAW_COST);
    deck.push_back(eastTradingPost);
    
    auto* westTradingPost = new CommercialCard("西方市场", 1, CommercialEffect::REDUCE_MANUFACTURED_COST);
    deck.push_back(westTradingPost);
    
    auto* marketplace = new CommercialCard("市集", 1, CommercialEffect::REDUCE_MANUFACTURED_COST);
    deck.push_back(marketplace);
    
    // ========== 红色卡牌(军事建筑) ==========
    auto* stable = new MilitaryCard("马厩", 1, 1);
    stable->setChainSymbol("STABLE");
    deck.push_back(createCardWithCost(stable, {{ResourceType::WOOD, 1}}));
    
    auto* barracks = new MilitaryCard("兵营", 1, 1);
    deck.push_back(createCardWithCost(barracks, {{ResourceType::CLAY, 1}}));
    
    auto* garrison = new MilitaryCard("卫戍部队", 1, 1);
    deck.push_back(createCardWithCost(garrison, {{ResourceType::CLAY, 1}}));
    
    auto* guardTower = new MilitaryCard("瞭望塔", 1, 1);
    deck.push_back(guardTower);
    
    return deck;
}

std::vector<Card*> CardFactory::createAgeIIDeck() {
    std::vector<Card*> deck;
    
    // ========== 棕色卡牌(原材料) ==========
    auto* sawmill = new RawMaterialCard("锯木厂", 2, ResourceType::WOOD, 2);
    sawmill->setCost(Cost(2));
    deck.push_back(sawmill);
    
    auto* brickyard = new RawMaterialCard("砖厂", 2, ResourceType::CLAY, 2);
    brickyard->setCost(Cost(2));
    deck.push_back(brickyard);
    
    auto* shelfQuarry = new RawMaterialCard("石场", 2, ResourceType::STONE, 2);
    shelfQuarry->setCost(Cost(2));
    deck.push_back(shelfQuarry);
    
    // ========== 灰色卡牌(制成品) ==========
    deck.push_back(new ManufacturedGoodCard("玻璃厂", 2, ResourceType::GLASS));
    deck.push_back(new ManufacturedGoodCard("烘干室", 2, ResourceType::PAPYRUS));
    
    // ========== 蓝色卡牌(平民建筑) ==========
    auto* aqueduct = new CivilianCard("渡槽", 2, 5);
    aqueduct->setChainedFrom("BATHS");
    deck.push_back(createCardWithCost(aqueduct, {{ResourceType::STONE, 3}}));
    
    auto* statue = new CivilianCard("雕像", 2, 4);
    statue->setChainedFrom("THEATER");
    statue->setChainSymbol("STATUE");
    deck.push_back(createCardWithCost(statue, {{ResourceType::WOOD, 2}, {ResourceType::CLAY, 1}}));
    
    auto* temple = new CivilianCard("神殿", 2, 4);
    temple->setChainSymbol("TEMPLE");
    deck.push_back(createCardWithCost(temple, {{ResourceType::GLASS, 1}, {ResourceType::PAPYRUS, 1}}));
    
    auto* courthouse = new CivilianCard("法院", 2, 5);
    deck.push_back(createCardWithCost(courthouse, {{ResourceType::CLAY, 2}, {ResourceType::GLASS, 1}}));
    
    auto* rostrum = new CivilianCard("讲坛", 2, 4);
    deck.push_back(createCardWithCost(rostrum, {{ResourceType::STONE, 1}, {ResourceType::WOOD, 1}}));
    
    // ========== 绿色卡牌(科学建筑) ==========
    auto* library = new ScientificCard("图书馆", 2, ScientificSymbol::TABLET, 2);
    library->setChainedFrom("SCRIPTORIUM");
    deck.push_back(createCardWithCost(library, {{ResourceType::STONE, 1}, {ResourceType::GLASS, 1}}));
    
    auto* school = new ScientificCard("学校", 2, ScientificSymbol::WHEEL, 1);
    school->setChainedFrom("WORKSHOP");
    school->setChainSymbol("SCHOOL");
    deck.push_back(createCardWithCost(school, {{ResourceType::WOOD, 1}, {ResourceType::PAPYRUS, 2}}));
    
    auto* laboratory = new ScientificCard("实验室", 2, ScientificSymbol::WHEEL, 1);
    laboratory->setChainSymbol("LABORATORY");
    deck.push_back(createCardWithCost(laboratory, {{ResourceType::WOOD, 1}, {ResourceType::GLASS, 2}}));
    
    auto* dispensary = new ScientificCard("药剂师", 2, ScientificSymbol::COMPASS, 2);
    dispensary->setChainedFrom("APOTHECARY");
    deck.push_back(createCardWithCost(dispensary, {{ResourceType::CLAY, 2}, {ResourceType::GLASS, 1}}));
    
    // ========== 黄色卡牌(商业建筑) ==========
    auto* forum = new CommercialCard("论坛", 2, CommercialEffect::RESOURCE_PRODUCTION);
    deck.push_back(createCardWithCost(forum, {{ResourceType::CLAY, 1}}));
    
    auto* caravansery = new CommercialCard("商队驿站", 2, CommercialEffect::RESOURCE_PRODUCTION);
    deck.push_back(createCardWithCost(caravansery, {{ResourceType::WOOD, 2}, {ResourceType::GLASS, 1}}));
    
    auto* customHouse = new CommercialCard("海关", 2, CommercialEffect::COINS_PER_CARD);
    customHouse->setImmediateCoins(4);
    customHouse->setCoinsPerCard(1, CardType::RAW_MATERIAL);
    deck.push_back(createCardWithCost(customHouse, {{ResourceType::CLAY, 2}, {ResourceType::PAPYRUS, 1}}));
    
    auto* brewery = new CommercialCard("酿酒厂", 2, CommercialEffect::COINS);
    brewery->setImmediateCoins(6);
    deck.push_back(brewery);
    
    // ========== 红色卡牌(军事建筑) ==========
    auto* walls = new MilitaryCard("城墙", 2, 2);
    walls->setChainSymbol("WALLS");
    deck.push_back(createCardWithCost(walls, {{ResourceType::STONE, 2}}));
    
    auto* horseBreeders = new MilitaryCard("马场", 2, 1);
    horseBreeders->setChainedFrom("STABLE");
    deck.push_back(createCardWithCost(horseBreeders, {{ResourceType::CLAY, 1}, {ResourceType::WOOD, 1}}));
    
    auto* archeryRange = new MilitaryCard("射箭场", 2, 2);
    deck.push_back(createCardWithCost(archeryRange, {{ResourceType::STONE, 1}, {ResourceType::WOOD, 1}, {ResourceType::PAPYRUS, 1}}));
    
    auto* trainingCamp = new MilitaryCard("训练营", 2, 2);
    trainingCamp->setChainSymbol("TRAINING_CAMP");
    deck.push_back(createCardWithCost(trainingCamp, {{ResourceType::WOOD, 2}, {ResourceType::CLAY, 2}}));
    
    auto* paradeGround = new MilitaryCard("阅兵场", 2, 2);
    deck.push_back(createCardWithCost(paradeGround, {{ResourceType::CLAY, 1}, {ResourceType::GLASS, 1}}));
    
    return deck;
}

std::vector<Card*> CardFactory::createAgeIIIDeck() {
    std::vector<Card*> deck;
    
    // ========== 蓝色卡牌(平民建筑) ==========
    auto* pantheon = new CivilianCard("万神殿", 3, 7);
    pantheon->setChainedFrom("TEMPLE");
    deck.push_back(createCardWithCost(pantheon, {{ResourceType::CLAY, 1}, {ResourceType::WOOD, 1}, 
                                                   {ResourceType::GLASS, 2}, {ResourceType::PAPYRUS, 2}}));
    
    auto* gardens = new CivilianCard("花园", 3, 6);
    gardens->setChainedFrom("STATUE");
    deck.push_back(createCardWithCost(gardens, {{ResourceType::CLAY, 2}, {ResourceType::WOOD, 2}}));
    
    auto* townHall = new CivilianCard("市政厅", 3, 7);
    deck.push_back(createCardWithCost(townHall, {{ResourceType::STONE, 3}, {ResourceType::GLASS, 2}}));
    
    auto* palace = new CivilianCard("宫殿", 3, 8);
    deck.push_back(createCardWithCost(palace, {{ResourceType::CLAY, 1}, {ResourceType::STONE, 1}, {ResourceType::WOOD, 1},
                                                 {ResourceType::GLASS, 2}, {ResourceType::PAPYRUS, 2}}));
    
    auto* senate = new CivilianCard("元老院", 3, 6);
    deck.push_back(createCardWithCost(senate, {{ResourceType::WOOD, 2}, {ResourceType::STONE, 2}, {ResourceType::PAPYRUS, 1}}));
    
    // ========== 绿色卡牌(科学建筑) ==========
    auto* academy = new ScientificCard("学院", 3, ScientificSymbol::COMPASS, 3);
    academy->setChainedFrom("SCHOOL");
    deck.push_back(createCardWithCost(academy, {{ResourceType::STONE, 1}, {ResourceType::WOOD, 1}, {ResourceType::GLASS, 2}}));
    
    auto* study = new ScientificCard("研究所", 3, ScientificSymbol::WHEEL, 3);
    study->setChainedFrom("SCHOOL");
    deck.push_back(createCardWithCost(study, {{ResourceType::WOOD, 1}, {ResourceType::GLASS, 2}, {ResourceType::PAPYRUS, 1}}));
    
    auto* observatory = new ScientificCard("天文台", 3, ScientificSymbol::SCALES, 3);
    deck.push_back(createCardWithCost(observatory, {{ResourceType::STONE, 1}, {ResourceType::PAPYRUS, 2}, {ResourceType::GLASS, 1}}));
    
    // ========== 黄色卡牌(商业建筑) ==========
    auto* port = new CommercialCard("港口", 3, CommercialEffect::COINS_PER_CARD);
    port->setVictoryPoints(3);
    port->setCoinsPerCard(2, CardType::RAW_MATERIAL);
    deck.push_back(createCardWithCost(port, {{ResourceType::WOOD, 1}, {ResourceType::GLASS, 2}}));
    
    auto* arsenal = new CommercialCard("军火库", 3, CommercialEffect::COINS_PER_CARD);
    arsenal->setVictoryPoints(3);
    arsenal->setCoinsPerCard(1, CardType::MILITARY);
    deck.push_back(createCardWithCost(arsenal, {{ResourceType::CLAY, 2}, {ResourceType::WOOD, 2}, {ResourceType::GLASS, 1}}));
    
    auto* lighthouse = new CommercialCard("灯塔", 3, CommercialEffect::COINS_PER_CARD);
    lighthouse->setVictoryPoints(3);
    lighthouse->setCoinsPerCard(1, CardType::COMMERCIAL);
    deck.push_back(createCardWithCost(lighthouse, {{ResourceType::CLAY, 1}, {ResourceType::GLASS, 1}}));
    
    auto* arena = new CommercialCard("竞技场", 3, CommercialEffect::COINS_PER_CARD);
    arena->setVictoryPoints(3);
    // 奇迹计数需要特殊处理
    deck.push_back(createCardWithCost(arena, {{ResourceType::STONE, 1}, {ResourceType::WOOD, 1}, {ResourceType::GLASS, 2}}));
    
    auto* chamber = new CommercialCard("商会", 3, CommercialEffect::COINS_PER_CARD);
    chamber->setVictoryPoints(3);
    chamber->setCoinsPerCard(3, CardType::MANUFACTURED_GOOD);
    deck.push_back(createCardWithCost(chamber, {{ResourceType::PAPYRUS, 2}}));
    
    // ========== 红色卡牌(军事建筑) ==========
    auto* fortifications = new MilitaryCard("要塞", 3, 2);
    fortifications->setChainedFrom("WALLS");
    deck.push_back(createCardWithCost(fortifications, {{ResourceType::CLAY, 2}, {ResourceType::STONE, 1}, {ResourceType::PAPYRUS, 1}}));
    
    auto* siegeWorkshop = new MilitaryCard("攻城工坊", 3, 2);
    siegeWorkshop->setChainedFrom("LABORATORY");
    deck.push_back(createCardWithCost(siegeWorkshop, {{ResourceType::WOOD, 1}, {ResourceType::CLAY, 2}, {ResourceType::GLASS, 1}}));
    
    auto* pretorium = new MilitaryCard("禁卫军营", 3, 3);
    deck.push_back(pretorium);  // 免费
    
    auto* circus = new MilitaryCard("马戏团", 3, 2);
    circus->setChainedFrom("TRAINING_CAMP");
    deck.push_back(createCardWithCost(circus, {{ResourceType::STONE, 2}, {ResourceType::WOOD, 2}}));
    
    // 公会卡将在游戏开始时随机选择3张添加
    
    return deck;
}

std::vector<GuildCard*> CardFactory::createAllGuildCards() {
    std::vector<GuildCard*> guilds;
    
    auto* buildersGuild = new GuildCard("建筑师公会", GuildType::BUILDERS, 2);
    guilds.push_back(createCardWithCost(buildersGuild, {{ResourceType::CLAY, 3}, {ResourceType::GLASS, 2}}));
    
    auto* tradersGuild = new GuildCard("商人公会", GuildType::TRADERS, 1);
    guilds.push_back(createCardWithCost(tradersGuild, {{ResourceType::GLASS, 1}, {ResourceType::PAPYRUS, 1}, {ResourceType::CLAY, 1}}));
    
    auto* magistratesGuild = new GuildCard("治安官公会", GuildType::MAGISTRATES, 1);
    guilds.push_back(createCardWithCost(magistratesGuild, {{ResourceType::WOOD, 2}, {ResourceType::STONE, 1}, {ResourceType::GLASS, 1}}));
    
    auto* scientistsGuild = new GuildCard("科学家公会", GuildType::SCIENTISTS, 1);
    guilds.push_back(createCardWithCost(scientistsGuild, {{ResourceType::CLAY, 2}, {ResourceType::WOOD, 2}}));
    
    auto* shipownersGuild = new GuildCard("船主公会", GuildType::SHIPOWNERS, 1);
    guilds.push_back(createCardWithCost(shipownersGuild, {{ResourceType::WOOD, 1}, {ResourceType::STONE, 1}, 
                                                           {ResourceType::GLASS, 1}, {ResourceType::PAPYRUS, 1}}));
    
    auto* tacticiansGuild = new GuildCard("战术家公会", GuildType::TACTICIANS, 1);
    guilds.push_back(createCardWithCost(tacticiansGuild, {{ResourceType::STONE, 2}, {ResourceType::CLAY, 1}, {ResourceType::PAPYRUS, 1}}));
    
    auto* moneylendersGuild = new GuildCard("放贷者公会", GuildType::MONEYLENDERS, 0);
    // 免费
    guilds.push_back(moneylendersGuild);
    
    return guilds;
}

// 实现在下一个文件继续...

std::vector<WonderCard*> CardFactory::createAllWonderCards() {
    std::vector<WonderCard*> wonders;
    
    // 1. 金字塔
    auto* pyramids = new WonderCard("金字塔");
    pyramids->setVictoryPoints(9);
    wonders.push_back(createCardWithCost(pyramids, {{ResourceType::STONE, 3}}));
    
    // 2. 大灯塔
    auto* lighthouse = new WonderCard("大灯塔");
    lighthouse->setVictoryPoints(4);
    lighthouse->setReduceTradeCost(true);
    wonders.push_back(createCardWithCost(lighthouse, {{ResourceType::WOOD, 1}, {ResourceType::STONE, 1}, {ResourceType::GLASS, 2}}));
    
    // 3. 空中花园
    auto* hangingGardens = new WonderCard("空中花园");
    hangingGardens->setVictoryPoints(9);
    hangingGardens->setAllowReplay(true);
    wonders.push_back(createCardWithCost(hangingGardens, {{ResourceType::WOOD, 2}, {ResourceType::GLASS, 2}}));
    
    // 4. 宙斯神像
    auto* statueOfZeus = new WonderCard("宙斯神像");
    statueOfZeus->setVictoryPoints(3);
    // 军事优势时每个军事标记+1盾(需要特殊处理)
    wonders.push_back(createCardWithCost(statueOfZeus, {{ResourceType::WOOD, 1}, {ResourceType::STONE, 1}, {ResourceType::CLAY, 2}}));
    
    // 5. 阿尔忒弥斯神庙
    auto* templeOfArtemis = new WonderCard("阿尔忒弥斯神庙");
    templeOfArtemis->setCoinsReward(12);
    templeOfArtemis->setAllowReplay(true);
    wonders.push_back(createCardWithCost(templeOfArtemis, {{ResourceType::WOOD, 1}, {ResourceType::STONE, 1}, 
                                                             {ResourceType::GLASS, 1}, {ResourceType::PAPYRUS, 1}}));
    
    // 6. 摩索拉斯陵墓
    auto* mausoleum = new WonderCard("摩索拉斯陵墓");
    mausoleum->setVictoryPoints(2);
    mausoleum->setRecycleCard(true);
    wonders.push_back(createCardWithCost(mausoleum, {{ResourceType::CLAY, 2}, {ResourceType::GLASS, 2}}));
    
    // 7. 马戏竞技场
    auto* circusMaximus = new WonderCard("马戏竞技场");
    circusMaximus->setVictoryPoints(3);
    circusMaximus->setMilitaryPowerBonus(1);
    circusMaximus->setDestroyOpponentCard(true);
    wonders.push_back(createCardWithCost(circusMaximus, {{ResourceType::STONE, 2}, {ResourceType::WOOD, 2}}));
    
    // 8. 巨像
    auto* colossus = new WonderCard("巨像");
    colossus->setVictoryPoints(3);
    colossus->setMilitaryPowerBonus(2);
    wonders.push_back(createCardWithCost(colossus, {{ResourceType::CLAY, 3}}));
    
    // 9. 亚历山大图书馆
    auto* greatLibrary = new WonderCard("亚历山大图书馆");
    greatLibrary->setVictoryPoints(4);
    // 随机获得进度标记(需要特殊处理)
    wonders.push_back(createCardWithCost(greatLibrary, {{ResourceType::WOOD, 1}, {ResourceType::PAPYRUS, 3}}));
    
    // 10. 比雷埃夫斯港
    auto* piraeus = new WonderCard("比雷埃夫斯港");
    piraeus->setVictoryPoints(2);
    piraeus->setReduceTradeCost(true);
    piraeus->setAllowReplay(true);
    wonders.push_back(createCardWithCost(piraeus, {{ResourceType::WOOD, 1}, {ResourceType::STONE, 1}, {ResourceType::CLAY, 2}}));
    
    // 11. 阿庇亚大道
    auto* viaAppia = new WonderCard("阿庇亚大道");
    viaAppia->setVictoryPoints(3);
    viaAppia->setOpponentCoinLoss(3);
    viaAppia->setAllowReplay(true);
    wonders.push_back(createCardWithCost(viaAppia, {{ResourceType::CLAY, 2}, {ResourceType::STONE, 2}}));
    
    // 12. 斯芬克斯
    auto* sphinx = new WonderCard("斯芬克斯");
    sphinx->setVictoryPoints(6);
    sphinx->setAllowReplay(true);
    wonders.push_back(createCardWithCost(sphinx, {{ResourceType::WOOD, 1}, {ResourceType::STONE, 1}, {ResourceType::GLASS, 2}}));
    
    return wonders;
}
