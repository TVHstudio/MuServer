/****** Object:  StoredProcedure [dbo].[WZ_LuckyItemDelete]    Script Date: 08/16/2014 19:03:45 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****************************************************************
-- 2.CREATE PROC
*****************************************************************/

/****************************************************************
TITLE    :	钒虐酒捞袍 昏力

EX       :	WZ_LuckyItemDelete

PROJECT  :	Season 6

CALL     : 

INPUT    : 

OUTPUT   :	@ErrorCode 
			0 : 己傍
			2 : 角菩

REVERSION:
-------------------------------------------------------------------
DATE		Author				Description		
-------------------------------------------------------------------
2010-09-16	傍饶琶[MU_STUDIO]	弥檬 累己
-------------------------------------------------------------------	
*****************************************************************/
CREATE  PROC  [dbo].[WZ_LuckyItemDelete]
@CharacterName varchar(10)
,@ItemCode	int
,@ItemSerial	bigint
AS  
DELETE	T_LUCKY_ITEM_INFO 
WHERE	CharName = @CharacterName AND ItemCode = @ItemCode AND ItemSerial = @ItemSerial

