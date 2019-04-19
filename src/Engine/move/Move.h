/*
 * ========================= Move.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.01.13
 *                                        MODIFY --
 * ----------------------------------------------------------
 *   Crawl / Fly 整合管理类
 * ----------------------------
 */
#ifndef _TPR_MOVE_H_
#define _TPR_MOVE_H_

//-------------------- CPP --------------------//
#include <functional>

//-------------------- Engine --------------------//
#include "Crawl.h"
#include "Fly.h"
#include "SpeedLevel.h"
#include "AnchorPos.h"
#include "MapCoord.h"

//-- need --
class GameObj;
class GameObjPos;
class Collision;


//-- 初级版本，在未来可能会发展成 数个 crawl实例 ／ 数个 fly实例
class Move{
public:
    Move() = default;

    //- 在 gameObj.init() 中被调用 --
    inline void init(   GameObj *_goPtr, 
                        GameObjPos *_goPosPtr,
                        Collision *_collisionPtr ){ //-- MUST --
        this->goPtr    = _goPtr;
        this->goPosPtr = _goPosPtr;

        this->crawl.init( this->goPtr, 
                        (Move*)this, 
                        this->goPosPtr, 
                        _collisionPtr ); 

        this->fly.init( (Move*)this, 
                        goPosPtr );
    }

    inline void RenderUpdate(){
        (this->isCrawl==true) ? 
                this->crawl.RenderUpdate() : 
                this->fly.RenderUpdate();
    }

    //------- flags -------//
    inline bool is_crawl() const {
        return this->isCrawl;
    }

    //------- set -------//
    inline void set_MoveType( bool _is_crawl ){
        this->isCrawl = _is_crawl;
    }
    inline void set_speedLv( SpeedLevel _lv ){
        this->speedLv = _lv;
    }
    inline void set_newCrawlDir( const NineBox &_newNB ){
        assert( this->isCrawl == true );
        crawl.set_newCrawlDir( _newNB );
    }
    inline void set_newflyIns( const FlyIns &_newFlyIns ){
        assert( this->isCrawl == false );
        this->fly.set_newflyIns( _newFlyIns );
    }
    inline void set_maskCountLimit( int _limit ){
        assert( this->isCrawl == false );
        this->fly.set_maskCountLimit( _limit );
    }

    //------- get -------//
    inline const SpeedLevel &get_speedLv() const {
        return this->speedLv;
    }

private:
    GameObj     *goPtr    {nullptr}; //- 每个 fly实例 都属于一个 go实例, 强关联
    GameObjPos  *goPosPtr {nullptr};

    Crawl   crawl   {}; //- 未来可能被拓展为 一组 crawl实例
    Fly     fly     {}; //- 未来可能被拓展为 一组 fly实例

    SpeedLevel   speedLv  { SpeedLevel::LV_3 }; //- 未来可能被拓展为 一组 speedLv数据集

    //===== flags =====//
    bool    isCrawl  {true};
};


#endif 

