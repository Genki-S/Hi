class Api::V1::MessagesController < Api::V1::ApplicationController
  protect_from_forgery with: :null_session

  before_action :cors_set_access_control_headers

  def pn_value
    message = URI.unescape(params[:message])
    pn_value = calculate_pn_value(message)
    render json: { message: message, pn_value: pn_value }, status: :ok
  end

  private
    def calculate_pn_value(message)
      require 'MeCab' # FIXME: not here
      pn_value = 0
      mecab = MeCab::Tagger.new("-Ochasen")
      node = mecab.parseToNode(message)
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
    end
end
