class Message < ActiveRecord::Base
  acts_as_paranoid

  belongs_to :user, primary_key: 'uid', foreign_key: 'from_uid'

  after_create :calculate_pn_value

  scope :today, lambda { where('sent_at BETWEEN ? AND ?', DateTime.now.beginning_of_day, DateTime.now.end_of_day) }

  def self.generate_default_messages_for(user)
    messages = [
      {
        body: 'heartlinkへようこそ！',
        sent_time: '06:00',
        pn_value: 0
      },
      {
        body: 'これはネガティブなメッセージです',
        sent_time: '08:30',
        pn_value: -1
      },
      {
        body: 'これはポジティブなメッセージです',
        sent_time: '07:30',
        pn_value: 1
      },
      {
        body: 'メッセージをゴミ箱にドラッグして消してみましょう',
        sent_time: '10:00',
        pn_value: 0
      },
      {
        body: '自分にメッセージを送って遊んでみましょう',
        sent_time: '03:00',
        pn_value: -0.8
      },
      {
        body: '新規メッセージは緑ボタンをタップ',
        sent_time: '18:20',
        pn_value: 0.7
      },
    ]

    messages.each do |data|
      data[:to_uid] = user.uid
      data[:sent_at] = Time.parse(data[:sent_time])
      data.reject! { |k, v| k == :sent_time }
      message = Message.create(data)
      message.update_attributes(pn_value: data[:pn_value])
    end
  end

  private
    def calculate_pn_value
      require 'MeCab' # FIXME: not here
      pn_value = 0
      mecab = MeCab::Tagger.new("-Ochasen")
      node = mecab.parseToNode(self.body)
      prototypes = []
      while node
        prototype = node.feature.split(/,/)[6]
        prototypes.push(prototype) unless prototype == '*'
        node = node.next
      end

      pn_values = PnJpWord.where(word: prototypes).pluck(:value)
      pn_value = if pn_values.size > 0
                   pn_values.sum / pn_values.size.to_f
                 else
                   0
                 end
      self.update_attributes(pn_value: pn_value)
    end
end
