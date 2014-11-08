class User < ActiveRecord::Base

  has_many :messages, primary_key: 'uid', foreign_key: 'to_uid'
  has_many :sent_messages, class_name: 'Message', primary_key: 'uid', foreign_key: 'from_uid'

  def self.create_with_omniauth(auth)
    create! do |user|
      user.provider = auth['provider']
      user.uid = auth['uid']
      if auth['info']
         user.name = auth['info']['name'] || ""
      end
    end
  end

end
