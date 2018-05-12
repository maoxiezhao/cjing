local BulletTempl = {}
BulletTempl.name = "bullet"

-- 子弹的cfg格式
BulletTempl.cfg = {
	demage = 1,
	speed = 200,
}

-- meta method，可以在各个bullet中重载各个方法
BulletTempl.metatable = {
	InitSprite = function(self, sprite_name)
		local spritePath = "entities/bullets"
		local sprite = self:CreateSprite(spritePath)
		if sprite then 
			sprite:SetAnimation(sprite_name .. "_normal")
			sprite:Start()

			local attachPos = self:GetAttachPos()
			sprite:SetPos(attachPos)
			sprite:SetRotateAnchor(8, 8)	
			self._sprite = sprite
		end
	end,

	InitBullet = function(self, templ_name, cfg)
		-- prop set
		self._demage = cfg.demage
		self._speed = cfg.speed
		self._offset = cfg.offset

		self._templ_name = templ_name

		self:InitSprite(templ_name)
	end,

	SetFireEntity = function(self, entity, weapon)
		if not entity or not weapon then return end

		local pos = entity:GetPos()
		pos[2] = pos[2] + 6
		self:SetPos(pos)

		local degree = entity:GetFacingDegree()
		self:SetFacingDegree(-degree)
	end,

	Firing = function(self)
		local movement = StraightMovement.Create()
		if movement then 
			movement:Start(self)

			local degree = self:GetFacingDegree()
			movement:SetSpeed(self._speed)
			movement:SetMaxDistance(1000)
			
			degree = degree + (math.random() * 2 - 1) * self._offset
			movement:SetAngle(-degree)
		end
	end,

	Boom = function(self, boom_name)
		local spritePath = "entities/boom"
		local sprite = self:CreateSprite(spritePath)
		if sprite then 
			sprite:SetAnimation(boom_name)
			sprite:SetDeferredDraw(false)
			sprite:Start()

			local degree = self:GetFacingDegree()
			local attachPos = self:GetAttachPos()
			sprite:SetPos(attachPos)
			sprite:SetRotateAnchor(8, 8)
			sprite:SetRotation(degree)
			sprite:SetAnchor(0.0, 0.2)
		end
	end,

	DemageEnemy = function ( self, enemy )
		local demage = self._demage
		if demage and enemy then 
			enemy:AddLife(-demage)
		end
	end
}

return BulletTempl