# Python API
  
## Index
- [Enumerator](#Enumerator)
- [Agent API](#Agent)
- [Object API](#Object)
- [Rule API](#Rule)
- [Game API](#Game)

  
## Enumerator

### Action
```Action을 정의하는 Enumerator입니다.```
- UP : 위로 이동
- DOWN : 아래로 이동
- LEFT : 왼쪽으로 이동
- RIGHT : 오른쪽으로 이동
- STAY : 가만히 있기 (스페이스)
- COUNT : Action의 개수

### GameResult
```게임의 결과를 정의하는 Enumerator입니다.```
- INVALID : 게임의 결과가 유효하지 않음
- WIN : 승리함
- DEFEAT : 패배함
- COUNT : GameResult의 개수

### Direction
```오브젝트의 방향을 정의하는 Enumerator입니다.```
- INVALID : 방향이 유효하지 않음
- UP : 위쪽
- DOWN : 아래쪽
- LEFT : 왼쪽
- RIGHT : 오른쪽

### ObjectType
```오브젝트의 종류를 정의하는 Enumeartor입니다.```  
자세한 내용은 아래 파일을 참고하세요.
- Includes/Baba/Enums/ObjectType.def
- Includes/Baba/Enums/PropertyType.def
- Includes/Baba/Enums/TextType.def
- Includes/Baba/Enums/VerbType.def

### VerbType
```문장의 종류를 정의하는 Enumerator입니다.```  
자세한 내용은 아래 파일을 참고하세요.
- Includes/Baba/Enums/VerbType.def

### PropertyType
```속성의 종류를 정의하는 Enumerator입니다.```  
자세한 내용은 아래 파일을 참고하세요.
- Includes/Baba/Enums/PropertyType.def

### 타입 변경 도구
- ObjectToProperty(type)  
```ObjectType의 type를 PropertyType으로 변경합니다.```
- PropertyToObject(type)  
```PropertyType의 type를 ObjectType으로 변경합니다.```

  
## Agent
Agent 클래스를 상속받아 에이전트를 만들 수 있습니다. 만든 Agent 클래스는 `Game`을 입력받으면 `Action`을 반환하는 메소드를 가지고 있어야 합니다. 아래는 Agent의 예시입니다.

```
class MyAgent(pyBaba.Agent):
    def GetAction(self, game):
        return pyBaba.Action.STAY
```
  
## Object
```게임 내 오브젝트 클래스입니다.```
### 메소드
- GetID() -> int  
```오브젝트의 ID를 반환합니다.```
- IsText() -> bool  
```오브젝트가 Text인지 여부를 반환합니다.```
- SetText(value:bool) -> Object  
```value가 True이면 오브젝트를 Text로 만듭니다.```
- SetType(type:ObjectType) -> Object  
```오브젝트의 타입을 변경합니다.```
- GetType() -> ObjectType  
```오브젝트의 타입을 반환합니다.```
- AddProperty(type:PropertyType) -> Object  
```오브젝트에 속성을 추가합니다.```
- RemoveProperty(type:PropertyType)  
```오브젝트의 속성을 제거합니다.```
- HasProperty(type:PropertyType) -> bool  
```오브젝트가 해당 속성을 가지고 있는지 여부를 반환합니다.```
- Destroy()  
```오브젝트를 파괴합니다.```
- IsDestroyed() -> bool  
```오브젝트가 파괴되었는지 여부를 반환합니다.```
  
## Rule
```게임의 규칙 클래스입니다.```
### 메소드
- GetTarget() -> ObjectType  
```규칙의 목표의 타입을 반환합니다.```
- GetVerb() -> ObjectType  
```규칙의 동사의 타입을 반환합니다.```
- GetEffect() -> ObjectType  
```규칙의 효과의 타입을 반환합니다.```
- GetRuleID() -> int  
```규칙의 ID를 반환합니다.```
- [static] CalculateRuleID(target:ObjectType, verb:ObjectType, effect:ObjectType) -> int  
```규칙의 ID를 계산합니다.```
  
## Game
```게임 클래스입니다.```
### 생성자
- (width, height)  
```가로 width, 세로 height 크기의 게임을 생성합니다.```

### 메소드
- GetWidth() -> int  
```게임의 가로 길이를 반환합니다.```
- GetHeight() -> int  
```게임의 세로 길이를 반환합니다.```
- At(x:int, y:int) -> list(Object)  
```(x, y)에 있는 오브젝트의 목록을 반환합니다.```
- Put(x:int, y:int) -> Object  
```(x, y)에 오브젝트를 배치합니다.```
- DestroyObject(obj:Object)  
```오브젝트를 파괴합니다.```
- FindObjects(func, excludeText:bool) -> list(Object)  
```func를 만족하는 오브젝트의 목록을 반환합니다. excludeText가 True이면 Text 오브젝트는 배제합니다.```
- FindObjectsByType(type:ObjectType, excludeText:bool) -> list(Object)  
```특정 type인 오브젝트의 목록을 반환합니다. excludeText가 True이면 Text 오브젝트는 배제합니다.```
- FindObjectsByProperty(type:PropertyType), excludeText:bool) -> list(Object)  
```특정 Property를 가진 오브젝트의 목록을 반환합니다. excludeText가 True이면 Text 오브젝트는 배제합니다.```
- FindObjectsByPosition(obj:Object, excludeText:bool) -> list(Object)  
```obj와 같은 위치를 공유하는 오브젝트의 목록을 반환합니다. excludeText가 True이면 Text 오브젝트는 배제합니다.```
- FilterObjectsByFunction(objs:list(Object), func) -> list(Object)  
```func를 만족하는 오브젝트만 objs에서 추려냅니다.```
- GetPositionByObject(obj:Object) -> tuple(int, int)  
```obj의 위치를 반환합니다.```
- ValidatePosition(x:int, y:int) -> bool  
```유효한 위치인지 여부를 반환합니다.```
- Update(action:Action)  
```게임을 업데이트합니다.```
- GetGameResult() -> GameResult  
```게임의 결과를 반환합니다.```
- AddRule(target:ObjectType, verb:ObjectType, effect:ObjectType) -> int  
```게임의 규칙을 추가하고, 추가된 규칙의 ID를 반환합니다.```
- AddBaseRule(target:ObjectType, verb:ObjectType, effect:ObjectType) -> int  
```게임의 기반 규칙을 추가하고, 추가된 규칙의 ID를 반환합니다. 추가된 규칙은 제거되지 않습니다.```
- RemoveRule(id:int)  
```게임의 규칙을 제거합니다.```
- TieStuckMoveableObjects(pusher:Object, dir:Direction)  
- MoveObjects(objs:list(Object), dir:Direction)  
```물체들을 이동합니다.```
- GetNowAction() -> Action  
```최근 한 행동을 반환합니다.```