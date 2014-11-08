class MessageSerializer < ActiveModel::Serializer
  attributes :id, :body, :pn_value, :sent_at, :opened_at
end
