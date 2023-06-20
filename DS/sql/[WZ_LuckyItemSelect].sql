/****** Object:  StoredProcedure [dbo].[WZ_LuckyItemSelect]    Script Date: 08/16/2014 19:04:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

/****************************************************************
TITLE    :	钒虐酒捞袍 炼雀

EX       :	WZ_LuckyItemSelect

PROJECT  :	Season 6

CALL     : 

INPUT    :  @CharacterName

OUTPUT   :	

REVERSION:
-------------------------------------------------------------------
DATE		Author				Description		
-------------------------------------------------------------------
2010-09-16	傍饶琶[MU_STUDIO]	弥檬 累己
-------------------------------------------------------------------	
*****************************************************************/
CREATE  PROC [dbo].[WZ_LuckyItemSelect]
@CharacterName varchar(10)  
AS  
SELECT	ItemCode, ItemSerial, DurabilitySmall 
FROM	T_LUCKY_ITEM_INFO 
WHERE	CharName = @CharacterName

